#include <stdio.h>
#include <stdlib.h>

// Função para expandir a matriz em linhas
int** expandirMatriz(int** matriz, int linhas, int colunas, int linhasExtras) {
    // Calcula o novo número total de linhas
    int novasLinhas = linhas + linhasExtras;

    // Aloca uma nova matriz com as dimensões atualizadas
    int** novaMatriz = (int**)malloc(novasLinhas * sizeof(int*));
    for (int i = 0; i < novasLinhas; i++) {
        novaMatriz[i] = (int*)malloc(colunas * sizeof(int));
    }

    // Copia os elementos da matriz original para a nova matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j] = matriz[i][j];
        }
    }

    // Libera a memória alocada pela matriz original
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    // Retorna o ponteiro para a nova matriz
    return novaMatriz;
}

int main() {
    // Cria uma matriz 3x3
    int linhas = 3;
    int colunas = 3;
    int** matriz = (int**)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
    }

    // Preenche a matriz com alguns valores
    int contador = 1;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = contador;
            contador++;
        }
    }

    // Expande a matriz adicionando 2 linhas extras
    int linhasExtras = 2;
    matriz = expandirMatriz(matriz, linhas, colunas, linhasExtras);

    // Imprime a matriz expandida
    int novasLinhas = linhas + linhasExtras;
    for (int i = 0; i < novasLinhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Libera a memória alocada pela matriz expandida
    for (int i = 0; i < novasLinhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
