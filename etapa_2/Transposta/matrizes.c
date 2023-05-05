#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

complexo** allocateComplexMatrix(int linhas, int colunas)
{
    complexo **matrix;

    matrix = (complexo **) malloc(linhas*sizeof(complexo*));

    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para cada linha da matriz
    for (int i = 0; i < colunas; i++)
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


complexo** transposta(complexo** c,int linhas, int colunas)
{
	complexo** mtx;
	mtx = allocateComplexMatrix(linhas,colunas);
	for (int j = 0; j < linhas; j++)
    {
        for (int d = 0; d < colunas; c++)
        {
            mtx[j][d].real = c[d][j].real;
			mtx[j][d].img = c[d][j].img;
        }
    }
	return mtx;
}
	