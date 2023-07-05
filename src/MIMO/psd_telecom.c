#include <stdio.h>
#include <stdlib.h>
#include "../matrizes/matrizes.h"
#include <gsl/gsl_linalg.h>
#include <time.h>

int * tx_data_read(FILE *fp, long int numBytes){

    int *s = (int *)malloc(numBytes * 4 * sizeof(int));
    if (s == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(fp);
        return (int *)1;
    }
    
    for (int i = 0; i < numBytes; i++) {
        char byte;
        fread(&byte, sizeof(byte), 1, fp);

        for (int j = 0; j <= 7; j=j+2) {
            int bit = (byte >> j) & 3;
            s[(i*4) + (j/2)]= bit;
        }
        
    }
    return s;
}


void rx_data_write(int *s, long int numBytes) {
    FILE *out = fopen("saida", "wb");
    if (out == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    else
        printf("Arquivo com a mensagem recebida criada com sucesso\n");

    for (int i = 0; i < numBytes; i++) {
        unsigned char byte = 0;
        for (int j = 0; j < 4; j++) {
            unsigned int bit = s[(i * 4) + j];
            byte |= (bit << (2 * j));
        }
        fwrite(&byte, sizeof(byte), 1, out);
    }

    fclose(out);
}

complexo* tx_qam_mapper(int *s, long int numBytes){
    complexo *c1 = (complexo *)malloc(numBytes * 4 * sizeof(complexo));   
    for(int i= 0; i<numBytes*4;i++){
        if(s[i]==0){
            c1[i].real = -1;
            c1[i].img = 1;
        }
        else if (s[i]==1){
            c1[i].real = -1;
            c1[i].img = -1;
        }
        else if (s[i]==2){
            c1[i].real = 1;
            c1[i].img = 1;
        }
        else {
            c1[i].real = 1;
            c1[i].img = -1;
        }
    }
    return c1;
}

int* rx_qam_demapper(complexo * map, long int numBytes){

    int *vetor = (int *)malloc(numBytes * 4 * sizeof(int));
      if (vetor == NULL) {
        printf("Erro na alocação de memória\n");
        return (int *)1;
    }   
    for(int i= 0; i<numBytes*4;i++){
        if(map[i].real== -1 && map[i].img == 1){
            vetor[i]=0;
        }
        else if (map[i].real== -1 && map[i].img == -1){
            vetor[i]=1;
        }
        else if (map[i].real== 1 && map[i].img == 1){
            vetor[i]=2;
        }
        else {
            vetor[i]=3;
        }
    }
    return vetor;
}

float ** channel_gen(int Nr, int Nt){
    float** H;
	
    H = (float **) malloc(Nr*sizeof(float*));
	
    if (H == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //Alocação de memória para cada linha da matriz
    for (int i = 0; i < Nr; i++)
    {
        H[i] = (float *) malloc(Nt*sizeof(float));
        if (H[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    srand(time(NULL));
    for (int i = 0; i < Nr; i++) {
        for (int j = 0; j < Nt; j++) {
            H[i][j] = -1 + 2 * ((float)rand() / RAND_MAX);
        }
    }
    return H;
}

/// @brief 
/// @param v 
/// @param Nstream 
/// @param numBytes 
/// @return Matriz complexa 
complexo ** tx_layer_mapper(complexo *v, int Nstream, long int numBytes){
    complexo **mtx_stream;
    mtx_stream = (complexo**) malloc(Nstream*numBytes*sizeof(complexo*));

    for(int i = 0; i < Nstream; i++){
        mtx_stream[i] = (complexo *) malloc(numBytes*Nstream*sizeof(complexo));
    }
    for (int i = 0; i < numBytes*4; i++){
        mtx_stream[i%Nstream][i/Nstream] = v[i];
    }
    return mtx_stream;
}

int main() {
    FILE* fp = fopen("teste", "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Solicitar ao usuário que escreva a mensagem
    printf("Digite a mensagem que quer enviar:\n");
    char mensagem[1000];
    fgets(mensagem, sizeof(mensagem), stdin);

    // Escrever a mensagem no arquivo
    fprintf(fp, "%s", mensagem);

    // Fechar o arquivo
    fclose(fp);

    // Abrir o arquivo para leitura em binario
    fp = fopen("teste", "rb");

    if (fp == NULL) {
        printf("Impossivel abrir o arquivo\n");
        return 1; // Encerra o programa se a abertura do arquivo falhar
    }

    printf("Arquivo criado com sucesso\n");
    fseek(fp, 0, SEEK_END);
    long int numBytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    int num_teste;
    printf("Insira quantos testes gostaria de fazer:"); scanf("%d",&num_teste);
    for(int teste = 1; teste<=num_teste; teste++){
        
        printf("\n=====================Teste Numero %d===================\n\n", teste);
        printf("Insira o valor de Antenas receptoras (Nr) e transmissoras (Nt):\n");
        int Nr; // Número de antenas recpetoras
        int Nt; // Número de antenas transmissoras
        
        printf("Nr:");scanf("%d",&Nr);
        printf("Nt:");scanf("%d",&Nt);
        int Nstream = Nr;
        // Leitura do arquivo
        printf("Realizando leitura do Arquivo...\n");
        int *s=tx_data_read(fp,numBytes);
        
        // Mapeamento dos bits do arquivo
        printf("Realizando Mapeamento dos Bits do Arquivo...\n");
        complexo *map = tx_qam_mapper(s,numBytes);

        // Criação do Canal H com range entre -1 e 1
        printf("Criação do Canal de transferencia de Dados:\n");
        float ** H = channel_gen(Nr,Nt);
        for(int l = 0; l<Nr;l++){
            for(int c = 0; c<Nt;c++){
                printf("%f ",H[l][c]);
            }
            printf("\n");
        }
        //Transformando o vetor complexo do mapaeamento para uma matriz complexa
        complexo **mtx= tx_layer_mapper(map, Nstream, numBytes);
        
        for(int l=0;l<Nstream;l++){
            for(int c=0; c<numBytes*2;c++){
                printf("%+f %+f",mtx[l][c].real,mtx[l][c].img);
            }
            printf("\n");
        }
        // Desmapeamento dos bits do arquivo
        printf("Realizando Desmapeamento dos Bits do Arquivo...\n");
        int *d=rx_qam_demapper(map,numBytes);

        // Leitura Final dos Dados
        printf("Salvando arquivo com a mensagem enviada...\n");
        rx_data_write(d,numBytes);
    }

    
    fclose(fp);
    return 0;
}