#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int main(void)
{
    complexo** c1,**c2; //matriz complexa a ser transposta
    complexo** c3,**c4,**somado;
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=2;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);
	c3 = allocateComplexMatrix(nlinhas,ncolunas);
	c4 = allocateComplexMatrix(nlinhas,ncolunas);
    //Insira os valores de c1:
        for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = (3*l)-c;
				c1[l][c].img = c+l;
				c3[l][c].real = l+1;
				c3[l][c].img = (2*l)-c;
				c4[l][c].real = (5*l)+c;
				c4[l][c].img = l-c;
			}
    }
        printf("=========Matriz A=========\n");
        for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(c1[l][c]);
			}
        printf("\n");
    }
	int nlinhas_trans = ncolunas;
	int ncolunas_trans = nlinhas;
	
	printf("\n=========Transporta de A=========\n");
    c2 = transposta(c1,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
		{
			for (int c = 0; c < ncolunas_trans; c++)
			{
				printComplex(c2[l][c]);
			}
        printf("\n");
		}
        
	complexo c_mult,c_mult1,mult;
	c_mult.real = 1;
	c_mult.img = 2;
	c_mult1.real = 2;
	c_mult1.img = 3;
	
	printf("\n\n=========Multiplicacao de ");
	printComplex(c_mult);
	printComplex(c_mult1);
	printf("=========\n");
	
	mult = multcomp(c_mult,c_mult1);
	printComplex(mult);	
	
	printf("\n\n=========Matriz B=========\n");
	
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c3[l][c]);
				}
			printf("\n");
		}
	printf("\n=========Matriz C=========\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c4[l][c]);
				}
			printf("\n");
		}
	printf("\n\n=========Soma de B + C=========\n");
	somado = somacomp(c3,c4,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(somado[l][c]);
			}
        printf("\n");
	}
	return(0);
}
