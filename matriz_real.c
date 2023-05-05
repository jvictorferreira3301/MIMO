#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,i2,j2,k,w,x; //quantidade de linhas e colunas das duas matrizes
    printf("Quantas linhas e colunas tem sua matriz A:\n");
    scanf("%i %i",&i,&j);
    printf("Quantas linhas e colunas tem sua matriz B:\n");
    scanf("%i %i",&i2,&j2);

    float A[i][j],B[i2][j2],C[i][j2];

    printf("Quais os componentes da Matriz A:\n");
        for (k=0; k<i; k++){
            for ( w=0; w<j; w++)
                scanf ("%f", &A[k][w]);
        }

    printf("\nQuais os componentes da Matriz B:\n");
        for (k=0; k<i2; k++){
            for ( w=0; w<j2; w++)
                scanf ("%f", &B[k][w]);
        }

        for (k=0; k<i; k++){
            for ( w=0; w<j2; w++)
                C[k][w]= 0;
        }


        for(k=0;k<i;k++){
            for (w=0;w<j2;w++){
                for(x=0;x<j;x++)
                    C[k][w] = C[k][w]+ (A[k][x]*B[x][w]);
            }
        }
    printf("\nA Multiplicação de A*B vale:\n");
        for (k=0; k<i; k++){
            for ( w=0; w<j2; w++)
                printf("%f ", C[k][w]);
            printf("\n");
        }



    return 0;
}
