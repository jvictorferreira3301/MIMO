#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
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
int * tx_data_pedding(int*s,long int numBytes, int Nstream){
    if(numBytes%Nstream==0){
        return s;
    }
    else{
        int *resized_s = (int*) realloc(s,((numBytes*4)+(numBytes%Nstream))*sizeof(int));

        for(long int i = numBytes*4; i<(numBytes*4)+(numBytes%Nstream); i++){
            resized_s[i]=4;
        }
        return s;
    }     
}

int* tx_data_padding(int *s, long int numBytes, int Nstream){
    long int newSymbol = numBytes*4;
    if (numBytes*4%Nstream == 0){
        return s;
    }
    while(newSymbol%Nstream != 0)
        newSymbol++;
        int *resized_s = (int*) realloc(s,newBytes*sizeof(int));
        for (long int i = numBytes*4; i < newBytes*4; i++)
            resized_s[i] = 4;
        return resized_s;
    
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
        else if (s[i] == 3){
            c1[i].real = 1;
            c1[i].img = -1;
        }else {
            c1[i].real = 0;
            c1[i].img = 0;
        }
    }
    return c1;
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

float** channel_gen(int Nr, int Nt, float minValue, float maxValue){
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
            H[i][j] = ((float)rand() / RAND_MAX) * (maxValue - minValue) + minValue;
        }
    }
    return H;
}

void channel_svd(complexo** H, complexo** W, complexo* T, complexo** F, int linhas, int colunas){

    gsl_matrix * A = gsl_matrix_alloc(linhas, colunas);// U, onde U é sobreposto
    gsl_vector * S = gsl_vector_alloc(colunas); // S
    gsl_matrix * V = gsl_matrix_alloc(colunas, colunas); // V
    gsl_vector * work = gsl_vector_alloc(colunas);

    printf("\n\nMatriz H\n");
    for(int l = 0; l < linhas; l++){
        for(int c = 0; c < colunas; c++){
            printf("%f ", H[l][c].real);
            gsl_matrix_set(A, l, c, H[l][c].real);
        }
        printf("\n");
    }

    gsl_linalg_SV_decomp(A, V, S, work);

    for(int l=0; l<linhas; l++){
        for(int c=0; c<colunas; c++){
            W[l][c].real = gsl_matrix_get(A,l,c);
            W[l][c].img = 0;
        }
    }

    for(int l=0; l<colunas; l++){
            T[l].real = gsl_vector_get(S,l);
            T[l].img = 0;
        }

    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++){
            F[l][c].real = gsl_matrix_get(V,l,c);
            F[l][c].img = 0;
        }
    }
}

void tx_precoder(complexo* x, float** F, int Nr, int Nt){
    
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
    
    int Nr; // Número de antenas recpetoras
    int Nt; // Número de antenas transmissoras
    int num_teste = 1; // Numero de testes necessarios
    
    for(int teste = 1; teste<=num_teste; teste++){
        
        printf("\n=====================Teste %d===================\n\n", teste);
        
        if(teste<=4){
            Nr = 3;
            Nt = 4;
            
        }
        else if (teste>4 && teste>=8){
            Nr = 8;
            Nt = 8;
        }
        else if (teste>8 && teste<=12){
            Nr = 8;
            Nt = 32;
        }
        else{
            Nr = 16;
            Nt = 32;
        }
        printf("Numero de antenas recpetoras: %d // Numero de antenas Transmissoras: %d\n",Nr,Nt);
        int Nstream = Nr;
        // Leitura do arquivo
        printf("Realizando leitura do Arquivo...\n");
        int *s=tx_data_read(fp,numBytes);
        
        //Preenchimento por meio do data_pedding
        printf("Data pedding...\n");
        int *d=tx_data_padding(s,numBytes,numBytes,Nstream);
        int newBytes = sizeof(d);
        for (int i = 0; i < newBytes*4; i++){
            printf("%d, ", d[i]);
        }
        printf("\ndeus me ajude po favor\n");
        // Mapeamento dos bits do arquivo
        printf("Realizando Mapeamento dos Bits do Arquivo...\n");
        complexo *map = tx_qam_mapper(d,numBytes);

        // Criação do Canal H com range entre -1 e 1
        printf("Criação do Canal de transferencia de Dados:\n");
        float ** h = channel_gen(Nr,Nt,-1,1); // Criação de h em float
        complexo ** H = allocateComplexMatrix(Nr, Nt); // Allocação de H em complexo
        // Preenchendo a parte real de H com os elementos reais de h
        for(int l = 0; l < Nr; l++){
            for(int c = 0; c < Nt; c++){
                H[l][c].real = h[l][c];
                H[l][c].img = 0;
            }
        }
        // Imprimindo H
        for(int l = 0; l<Nr;l++){
            for(int c = 0; c<Nt;c++){
                printf("%+f ", H[l][c].real);
            }
            printf("\n");
        }
        // Chamada do cálculo SVD de H
        //printf("\nIniciando SVD(H)");
        complexo** U = allocateComplexMatrix(Nr,Nt);
        complexo* S = (complexo *) malloc(Nt*sizeof(complexo));
        complexo** V = allocateComplexMatrix(Nt,Nt);

        //channel_svd(H, U, S, V, Nr, Nt);

        /*for (int l = 0; l < Nr; l++){
            for (int c = 0; c < Nt; c++){
                printComplex(U[l][c]);
            }
            printf("\n");
        }*/
        //Transformando o vetor complexo do mapaeamento para uma matriz complexa
        complexo **mtx= tx_layer_mapper(map, Nstream, numBytes);
        printf("Matriz stream\n");
        for(int l=0;l<Nstream;l++){
            printf("[");
            for(int c=0; c<numBytes*2;c++){
                printf("%+.2f %+.2f, ",mtx[l][c].real,mtx[l][c].img);
            }
            printf("]\n");
        }
        printf("\n");
        // Desmapeamento dos bits do arquivo
        printf("Realizando Desmapeamento dos Bits do Arquivo...\n");
        int *a=rx_qam_demapper(map,numBytes);

        // Leitura Final dos Dados
        printf("Salvando arquivo com a mensagem enviada no arquivo test_Nr%d_Nt%d\n",Nr,Nt);
        rx_data_write(d,numBytes);
    }

    fclose(fp);
    return 0;
}