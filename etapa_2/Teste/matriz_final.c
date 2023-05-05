#include <stdio.h>
#include <stdlib.h>

void multmatriz (int i, int j, float A[][j], int i2, int j2, float B[][j2]);

int main()
{
	int i,j,i2,j2,k,w; //quantidade de linhas e colunas das duas matrizes
	printf("Quantas linhas e colunas tem sua matriz A:\n");
	scanf("%i %i",&i,&j);
	printf("\nQuantas linhas e colunas tem sua matriz B:\n");
	scanf("%i %i",&i2,&j2);

	float A[i][j],B[i2][j2],C[i][j2];
	/* A e B são as matrizes que queremos multiplicar e C a matriz resultado dessa multiplicação */

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

        if(i == j2){ //Teste para validar a multiplicação das matrizes.
        	for(k=0;k<i;k++){
			for(w=0;w<j2;w++)
				C[k][w] = 0; //inicializa C[k][w] com zero;
		}
		multmatriz(i,j,A,j2,i2,B);
		printf("\nA multiplicação de A*B é igual a:\n");
		for (k=0; k<i; k++){
            		for (w=0; w<j2; w++){
                		printf("%f ", C[k][w]);
                	}
                	printf("\n");
                }
	}
	else //Caso o teste seja invalido.
		printf("\nMultiplicação Inválida\n");

	return 0;
}
/* A função multmatriz tem como entrada os valores da coluna e linha das tabelas e as matrizes que queremos multiplicar e a matriz C como uma matriz 0 */
float multmatriz (int i, int j, float A[][j], int i2, int j2, float B[][j2])
{
	int k,w,x;
	float C[i][j2];
	for(k=0;k<i;k++){
		for(w=0;w<j2;w++){
			for (x=0;x<j;x++)
				C[k][w] = C[k][w]+ (A[k][x]*B[x][w]);
		}
	}
    return C;

}
