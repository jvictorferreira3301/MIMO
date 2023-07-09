#include <stdio.h>
#include <stdlib.h>

int* tx_data_read(const char* filename, long* file_size) {
    // Abrindo o arquivo no modo leitura
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Descobrindo o tamanho do arquivo para saber o quanto de memória deve ser alocada
    fseek(file, 0, SEEK_END); // Posicionando o ponteiro no final do arquivo
    *file_size = ftell(file); // Retornando a posição atual do ponteiro para obter o tamanho do arquivo em bytes
    fseek(file, 0, SEEK_SET); // Marcando o ponteiro no início do arquivo para que todas as leituras aconteçam a partir do início

    // Alocando memória para armazenar o conteúdo do arquivo
    char* content = (char*)malloc(*file_size + 1);
    if (content == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return NULL;
    }

    // Finalmente, lendo o arquivo
    fread(content, 1, *file_size, file);
    fclose(file);
    content[*file_size] = '\0'; // Adicionando um '\0' para indicar o fim da string

    // Agora temos que alocar memória para armazenar os números inteiros resultantes
    int* decimal_sequence = (int*)malloc(*file_size * 4 * sizeof(int)); // É necessário multiplicar o tamanho do arquivo por 4, pois são 4 números inteiros por byte
    if (decimal_sequence == NULL) {
        printf("Erro ao alocar memória.\n");
        //free(content);
        return NULL;
    }

    // Convertendo cada byte em 4 números inteiros de 0 a 3
    int byte;
    int index = 0;
    // Lendo cada byte do arquivo até o final
    while ((byte = *content++) != '\0') {
        decimal_sequence[index++] = (byte >> 6) & 0x03; // Atribuindo os dois bits mais significativos ao vetor resultado
        decimal_sequence[index++] = (byte >> 4) & 0x03;
        decimal_sequence[index++] = (byte >> 2) & 0x03;
        decimal_sequence[index++] = byte & 0x03;
    }

    //free(content); // Liberando a memória alocada para a string content

    return decimal_sequence;
}

int main() {
    const char* filename = "MIMO.txt";
    long file_size;
    int* resultado = tx_data_read(filename, &file_size);

    if (resultado != NULL) {
        // Imprime o vetor resultante
        for (int i = 0; i < file_size * 4; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");

        //free(resultado);
    }

    return 0;
}
