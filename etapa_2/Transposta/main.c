#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int main(void)
{
    complexo** c1,**c2; //matriz complexa a ser transposta
    int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=2;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);

    //Insira os valores de c1:
        for (int j = 0; j < nlinhas; j++)
		{
        for (int c = 0; c < ncolunas; c++)
        {
            c1[j][c].real = (3*j)-c;
                        c1[j][c].img = c+j;
        }
    }
        printf("Matriz A:\n");
        for (int j =0 ; j < nlinhas; j++)
		{
        for (int c = 0; c < ncolunas; c++)
        {
            printComplex(c1[j][c]);
        }
        printf("\n");
    }
		int nlinhas_trans = ncolunas;
		int ncolunas_trans = nlinhas;
        printf("\nTransporta de A:\n");
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
	printf("\n\n");
	mult = multcomp(c_mult,c_mult1);
	printComplex(mult);	
	
	return(0);
}
