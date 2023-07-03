#include <stdio.h>
#include <stdlib.h>

// Protótipo da Função tx_data read para a Atividade 5 - Implementação do Sistema de comunicação MIMO.
// jv - 03/07/2023 

int* tx_data_read(const char* filename, int* length) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return NULL; // Encerra o programa caso o arquivo não seja aberto corretamente 
    }
    
    printf("Arquivo %s aberto com sucesso \n", filename);

    // Obtenção do tamanho do arquivo
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alocaçã0 de memória para armazenar os dados
    unsigned char* contents = (unsigned char*)malloc(*length * sizeof(unsigned char));
    if (contents == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return NULL;
    }

    // Leitura do conteúdo do arquivo
    fread(contents, sizeof(unsigned char), *length, file);
    fclose(file);

    // Cálculo do tamanho necessário para o vetor de saída 
    int output_length = *length * 4;
    int* result = (int*)malloc(output_length * sizeof(int));
    if (result == NULL) {
        printf("Erro ao alocar memória.\n");
        free(contents);
        return NULL;
    }

    // Conversão de cada byte em quatro números inteiros
    for (int i = 0; i < *length; i++) {
        unsigned char byte = contents[i];

        // Conversão de byte em uma sequência binária de 8 bits
        char binary_string[9];
        binary_string[8] = '\0';
        for (int j = 0; j < 8; j++) {
            binary_string[j] = (byte & (1 << (7 - j))) ? '1' : '0';
        }

        // Separaração da sequência binária em quatro números inteiros
        for (int j = 0; j < 4; j++) {
            char bits[3];
            bits[0] = binary_string[j * 2];
            bits[1] = binary_string[j * 2 + 1];
            bits[2] = '\0';
            result[i * 4 + j] = strtol(bits, NULL, 2);
        }
    }

    free(contents);

    return result;
}

int main() {
    const char* filename = "exemplo.txt";
    int length;
    int* result = tx_data_read(filename, &length);
    if (result != NULL) {
        printf("Vetor resultante:\n");
        for (int j = 0; j < length * 4; j++) {
            printf("Bit %d: %u\n", j, result[j]);
        }
        printf("\n");

        free(result);
    }

    return 0;
}

