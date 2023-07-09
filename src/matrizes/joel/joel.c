#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float real;
    float img;
} complexo;

int * tx_data_read(FILE *fp, long int numBytes) {
    // Aloca memória para o array de inteiros
    int *s = (int *)malloc(numBytes * 4 * sizeof(int));
    if (s == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(fp);
        return NULL;
    }
    // Lê os bytes do arquivo e converte em inteiros de 2 bits
    for (int i = 0; i < numBytes; i++) {
        char byte;
        fread(&byte, sizeof(byte), 1, fp);

        for (int j = 0; j <= 7; j = j + 2) {
            int bit = (byte >> j) & 3;
            s[(i * 4) + (j / 2)] = bit;
        }
    }
    return s;
}

void rx_data_write(int *s, long int numBytes, char *fileName) {
    FILE *out = fopen(fileName, "wb");
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

complexo *tx_qam_mapper(int *s, long int numQAM) {
    // Aloca memória para o vetor de complexos
    complexo *c1 = (complexo *)malloc(numQAM * sizeof(complexo));
    if (c1 == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }
    for (int i = 0; i < numQAM; i++) {
        if (s[i] == 0) {
            c1[i].real = -1;
            c1[i].img = 1;
        } else if (s[i] == 1) {
            c1[i].real = -1;
            c1[i].img = -1;
        } else if (s[i] == 2) {
            c1[i].real = 1;
            c1[i].img = 1;
        } else if (s[i] == 3) {
            c1[i].real = 1;
            c1[i].img = -1;
        } else {
            c1[i].real = 0;
            c1[i].img = 0;
        }
    }
    return c1;
}

int main() {
    char *filename = "MIMO";
    char *filename_saida = "penis";

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // Realiza a leitura do arquivo e obtém a sequência de dígitos
    int *resultado = tx_data_read(fp, file_size);

    if (resultado != NULL) {
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d, ", resultado[i]);
        }
        printf("\n");

        // Escreve a sequência de dígitos no arquivo binário
        rx_data_write(resultado, file_size, filename_saida);
        // Mapeia os indices para os numeros complexos da constelacao qam
        complexo *map = tx_qam_mapper(resultado, file_size * 4);
        if (map != NULL) {
            // Imprime os numeros complexos
            for (int i = 0; i < file_size * 4; i++) {
                printf("Índice %d: %.2f%+.2fj\n", i, map[i].real, map[i].img);
            }
        }
        // Libera a memória alocada
    }

    fclose(fp);
    return 0;
}