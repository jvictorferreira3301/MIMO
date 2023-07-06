/// @file psd_telecom.c

#include <stdio.h>
#include <stdlib.h>
#include "../matrizes/matrizes.h"
#include <gsl/gsl_linalg.h>
#include <time.h>

/**
 * @brief Lê os dados de um arquivo e os converte em um array de inteiros.
 *
 * Esta função lê os dados binários de um arquivo e os converte em um array de inteiros,
 * em que cada inteiro representa 2 bits de dados. A função aloca memória dinamicamente
 * para o array de inteiros e retorna um ponteiro para o início do array.
 *
 * @param fp Ponteiro para o arquivo a ser lido.
 * @param numBytes O número de bytes a serem lidos do arquivo.
 * @return Um ponteiro para o array de inteiros que contém os dados convertidos, ou NULL
 *         em caso de erro na alocação de memória.
 *
 * @note O chamador é responsável por liberar a memória alocada para o array de inteiros
 *       quando não precisar mais dele, usando a função free().
 */
int * tx_data_read(FILE *fp, long int numBytes){
    // Aloca memória para o array de inteiros
    int *s = (int *)malloc(numBytes * 4 * sizeof(int));
    if (s == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(fp);
        return (int *)1;
    }
    // Lê os bytes do arquivo e converte em inteiros de 2 bits
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

/**
 * @brief Realiza o preenchimento (padding) dos dados com zeros.
 *
 * Esta função realiza o preenchimento (padding) dos dados com zeros para garantir
 * que o tamanho do array de inteiros seja um múltiplo inteiro do número de streams (Nstream).
 * Se o número de bytes (numBytes) for um múltiplo exato do número de streams, a função
 * retorna o array de inteiros original sem alterações. Caso contrário, a função realoca
 * memória para o array de inteiros e preenche o espaço adicional com zeros.
 *
 * @param s Ponteiro para o array de inteiros contendo os dados.
 * @param numBytes O número de bytes original antes do preenchimento.
 * @param Nstream O número de streams para o qual o tamanho do array deve ser um múltiplo.
 * @return Um ponteiro para o array de inteiros com o preenchimento realizado, ou NULL
 *         em caso de erro na alocação de memória.
 */
int * tx_data_pedding(int*s,long int numBytes, int Nstream){ //é padding marcão
    // Verifica se o número de bytes é um múltiplo do número de streams
    if((4*numBytes)%Nstream==0){
        return s;
    }
    else{
        // Realoca memória para o array de inteiros com o espaço adicional necessário
        int *resized_s = (int*)malloc(((numBytes*4)+((4*numBytes)%Nstream))*sizeof(int));
        // Preenche o espaço adicional com zeros
        for(long int i = numBytes*4; i<=(numBytes*4)+((4*numBytes)%Nstream); i++){
            resized_s[i]=4;
        }
        return s;
    }     
}

/**
 * @brief Mapeia os dados binários em uma sequência de símbolos QAM.
 *
 * Esta função mapeia os dados binários em uma sequência de símbolos QAM (Quadrature
 * Amplitude Modulation) representados por números complexos. A função aloca memória
 * dinamicamente para o vetor de complexos e retorna um ponteiro para o vetor.
 *
 * @param s Ponteiro para o array de inteiros contendo os dados binários.
 * @param numBytes O número de bytes contidos no array de inteiros.
 * @return Um ponteiro para o vetor de complexos que contém os símbolos QAM mapeados, ou NULL
 *         em caso de erro na alocação de memória.
 */

complexo* tx_qam_mapper(int *s, long int numBytes){
    // Aloca memória para o vetor de complexos
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
        else if(s[i]==3){
            c1[i].real = 1;
            c1[i].img = -1;
        }
        else{
            c1[i].real = 0;
            c1[i].img = 0;
        }
    }
    return c1;
}

/**
 * @brief Mapeia os dados de um vetor para uma matriz de complexos.
 *
 * Esta função mapeia os dados de um vetor de complexos em uma matriz de complexos,
 * onde cada posição da matriz representa um stream de transmissão. A função aloca
 * memória dinamicamente para a matriz de complexos e retorna um ponteiro para a matriz.
 *
 * @param v Ponteiro para o vetor de complexos contendo os dados a serem mapeados.
 * @param Nstream O número de streams de transmissão.
 * @param numBytes O número de bytes contidos no vetor de complexos.
 * @return Um ponteiro para a matriz de complexos que contém os dados mapeados, ou NULL
 *         em caso de erro na alocação de memória.
 */

complexo ** tx_layer_mapper(complexo *v, int Nstream, long int numBytes){
    // Aloca memória para a matriz de complexos
    complexo **mtx_stream;
    mtx_stream = (complexo**) malloc(Nstream*numBytes*sizeof(complexo*));

    for(int i = 0; i < Nstream; i++){
        mtx_stream[i] = (complexo *) malloc(numBytes*Nstream*sizeof(complexo));
    }
    // Mapeia os dados do vetor para a matriz de complexos
    for (int i = 0; i < numBytes*4; i++){
        mtx_stream[i%Nstream][i/Nstream] = v[i];
    }
    return mtx_stream;
}

complexo* rx_layer_demapper(complexo** mtx_stream, int Nstream, long int numBytes) {
    complexo* v = (complexo*) malloc(numBytes * 4 * sizeof(complexo));
    if (v == NULL) {
        printf("Erro na alocação de memória.\n");
        return NULL;
    }

    for (int i = 0; i < numBytes * 4; i++) {
        v[i] = mtx_stream[i % Nstream][i / Nstream];
    }

    return v;
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
int *rx_data_depadding(int *s, long int numBytes, int Nstream) {
    // Verifica se o número de bytes é um múltiplo do número de streams
    if ((4*numBytes) % Nstream == 0) {
        return s;
    } 
    else {
        // Cria um novo array para armazenar os valores originais
        int *resized_s = (int *)malloc(4*numBytes*sizeof(int));

        // Copia os valores originais de volta para o array redimensionado
        for (long int i = 0; i < 4*numBytes; i++) {
            resized_s[i] = s[i];
        }
        return resized_s;
    }
}


void rx_data_write(int* s, long int numBytes, char* fileName) {
    FILE* out = fopen(fileName, "wb");
    if (out == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", fileName);
        return;
    } else {
        printf("Arquivo %s criado com sucesso.\n", fileName);
    }

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


float ** channel_gen(int Nr, int Nt, float minValue, float maxValue){
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



int main() {
    FILE *fp;
    int num_teste = 1; // Numero de testes necessarios
    
    for(int teste = 1; teste<=num_teste; teste++){
        
    printf("\n=====================Teste %d===================\n\n", teste);
    fp = fopen("teste2", "rb");

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
        if(teste<=4){
            Nr = 3;
            Nt = 4;
            
        }
        else if (teste>4 && teste<=8){
            Nr = 8;
            Nt = 8;
        }
        else if (teste>8 && teste<=12){
            Nr = 8;
            Nt = 32;
        }
        else if (teste>12 && teste <=16){
            Nr = 16;
            Nt = 32;
        }

        int Nstream = Nr;
        printf("Numero de antenas recpetoras: %d // Numero de antenas Transmissoras: %d // Numero de fluxos: %d\n",Nr,Nt,Nstream);
        // Leitura do arquivo
        printf("Realizando leitura do Arquivo...\n");
        int *s=tx_data_read(fp,numBytes);
        for(int i = 0; i<numBytes*4; i++){
            printf("%d\n",s[i]);
        }
        //Preenchimento por meio do data_pedding
        printf("Data pedding...\n");
        int *d=tx_data_pedding(s,numBytes,Nstream);
        for(int i = 0; i<=numBytes*4+((4*numBytes)%Nstream); i++){
            printf("%d\n",s[i]);
        }
        // Mapeamento dos bits do arquivo
        //printf("Realizando Mapeamento dos Bits do Arquivo...\n");
        complexo *map = tx_qam_mapper(d,numBytes);

        // Criação do Canal H com range entre -1 e 1
        // printf("Criação do Canal de transferencia de Dados...\n");
        float ** H = channel_gen(Nr,Nt,-1,1);
        int ruido;
        float **Rd;
        if(teste == 1 || teste == 5 || teste == 9 || teste == 13){
            Rd=channel_gen(Nr,Nt,-1,1);
            ruido = 1;
        }
        else if(teste == 2 || teste == 6 || teste == 10 || teste == 14){
            Rd=channel_gen(Nr,Nt,-0.5,0.5);
            ruido = 2;
        }
        else if(teste == 3 || teste == 7 || teste == 11 || teste == 15){
            Rd=channel_gen(Nr,Nt,-0.1,0.1);
            ruido = 3;
        }
        else if(teste == 4 || teste == 8 || teste == 12 || teste == 16){
            Rd=channel_gen(Nr,Nt,-0.01,0.01);
            ruido = 4;
        }

        //Transformando o vetor complexo do mapaeamento para uma matriz complexa
        complexo **mtx= tx_layer_mapper(map, Nstream, numBytes);

        complexo *v=rx_layer_demapper(mtx,Nstream,numBytes);

        // Desmapeamento dos bits do arquivo
        //printf("Realizando Desmapeamento dos Bits do Arquivo...\n");
        int *a=rx_qam_demapper(v,numBytes);
        printf("Data repedding...\n");
        int *s_rest = rx_data_depadding(d,numBytes,Nstream);
        for(int i = 0; i<numBytes*4; i++){
            printf("%d\n",s_rest[i]);
        }
        // Leitura Final dos Dados
        printf("Salvando arquivo com a mensagem enviada no arquivo test_Nr%d_Nt%d_Rd%d\n",Nr,Nt,ruido);
        
        char fileName[100];
        sprintf(fileName, "Teste_Nr%d_Nt%d_Rd%d", Nr,Nt,ruido); // Formata o nome do arquivo com base no valor de i
        rx_data_write(s_rest, numBytes, fileName);
        free(s_rest);
    }

    fclose(fp);
    return 0;
}