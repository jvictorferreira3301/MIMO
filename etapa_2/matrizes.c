#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

complexo** allocateComplexMatrix (int linhas, int colunas)
{
    complexo** matrix;

    matrix = (complexo **) malloc(linhas*sizeof(complexo*));

    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para cada linha da matriz
    for (int i = 0; i < linhas; i++)
    {
        matrix[i] = (complexo *) malloc(colunas*sizeof(complexo));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    return matrix;
}

complexo** transposta(complexo** matriz,int linhas, int colunas)
{
        complexo** mtx;

        mtx = allocateComplexMatrix(colunas,linhas);
        for (int l = 0; l < linhas; l++)
		{
			for (int c = 0; c < colunas; c++)
			{
				mtx[l][c].real = matriz[c][l].real;
                mtx[l][c].img = matriz[c][l].img;
			}
		}
    return mtx;
}

complexo** soma(complexo** c2, complexo** c1, int linhas, int colunas)
{
	complexo** matrix;
	
	matrix = allocateComplexMatrix(linhas,colunas);
		for (int l = 0; l < linhas; l++)
		{
			for (int c = 0; c < colunas; c++)
			{
				matrix[l][c].real = c1[l][c].real + c2[l][c].real;
                matrix[l][c].img = c1[l][c].img + c2[l][c].img;
			}
		}
	return matrix;
}


void printComplex(complexo z)
{
    printf("%+.2f %+.2fj ", z.real, z.img);
}

complexo multcomp(complexo c, complexo c1)
{
	complexo multiplicado;
	multiplicado.real = (c.real*c1.real)-(c.img*c1.img);
	multiplicado.img = (c.real*c1.img)+(c.img*c1.real);
	return multiplicado;
}
void teste_transposta(void)
{
	complexo** c1,**c2; //matriz complexa a ser transposta
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=3;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);
	printf("\n===============================Teste da operação transposta=================================\n");
	
        for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = (3*l)-c;
				c1[l][c].img = c+l;
			}
    }
        printf("\nOperando A:\n");
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
	
	printf("\nResultado R:\n");
    c2 = transposta(c1,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
		{
			for (int c = 0; c < ncolunas_trans; c++)
			{
				printComplex(c2[l][c]);
			}
        printf("\n");
		}
}
