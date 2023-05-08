#include <stdio.h>
#include "matrizes.h"

#define max_lines 10
#define max_columns 10

int main() {
    int a = 2;
    int b = 2;

    complexo m1[2][2] = {{ {3, 6.4}, {0.6, 4} },
                              { {2, 1.5}, {-3, 8} }};

    complexo m2[2][2] = {{ {0.9, 7.1}, {2, 5} },
                              { {1.15, 4.1}, {1, 1} }};

    complexo resultado[2][2];

    subtracao(a, b, m1, m2, resultado); /* Chamamos a função subtração*/

    int i, j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
                printf("(%.2f + %.2fi) ", resultado[i][j].re, resultado[i][j].img);
        }
        printf("\n");
    }

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
    
    
    
    teste_subtracao(m, n, z1, z2, result); /* Chamamos a função subtração*/
    for(l = 0; l< m; l++) {
        for(c = 0; c < n; c++){ 
            printf("(%.2f + %.2fi) ", result[l][c].re, result[l][c].img);
            }
        printf("\n");
        }
    

}
