#include <stdio.h>
#include <stdlib.h>

void rx_data_write(const char* filename, const char* data) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    unsigned char byte = 0;
    int count = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        // Recuperar o valor original do byte
        byte = (byte << 2) | (data[i] - '0');
        count++;

        // Se 4 dígitos foram processados, escrever o byte no arquivo
        if (count == 4) {
            fputc(byte, file);
            byte = 0;
            count = 0;
        }
    }

    fclose(file);
}

int main() {
    const char* data = "13001201132113031201123212100022";
    const char* filename = "output.txt";

    rx_data_write(filename, data);

    return 0;
}

