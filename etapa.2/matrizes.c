#include <stdio.h>
#define max_lines 10
#define max_columns 10

typedef struct {
    float re; /* Parte real */
    float img; /* Parte Imaginária */
} complexo;

/* Implementação da função */
/* Sendo m1 definida como uma matriz de numero complexo assim como m2 */

void subtracao(int a, int b, complexo m1[a][b], complexo m2[a][b], complexo resultado[a][b]) {
int i, j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            resultado[i][j].re = m1[i][j].re - m2[i][j].re;
            resultado[i][j].img = m1[i][j].img - m2[i][j].img;
        }
    }
}

void teste_subtracao(int m, int n, complexo z1[m][n], complexo z2[m][n], complexo result[m][n]) {
int l, c;
    for (l = 0; l < m; l++) {
        for (c = 0; c < n; c++) {
            result[l][c].re = z1[l][c].re - z2[l][c].re;
            result[l][c].img = z1[l][c].img - z2[l][c].img;

int m,n; 
    printf("Insira o numero de linhas (%d): \n", max_lines);
    scanf("%d", &m);
    printf("Insira o numero de colunas (%d): \n", max_columns);
    scanf("%d", &n);


complexo z1[m][n],z2[m][n], result[m][n];
    

    int l, c;
    for (l = 0; l < m; l++) {
        for (c = 0; c < n; c++) {
            printf("Informe os valores da primeira matriz:\n");
            printf("Parte real: ");
            scanf("%f", &z1[l][c].re);
            printf("Parte imaginaria: ");
            scanf("%f", &z1[l][c].img);  

        }
    }
    
    
    printf("\n Informe os valores da segunda matriz:\n");
    for (l = 0; l < m; l++) {
        for (c = 0; c < n; c++) {
            printf("Parte real: ");
            scanf("%f", &z2[l][c].re);
            printf("Parte imaginaria: ");
            scanf("%f", &z2[l][c].img);
         }
    }
        }
    }
}



