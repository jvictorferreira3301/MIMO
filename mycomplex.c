#include <stdio.h>
#include <stdlib.h>
#include "mycomplex.h"

Complexo **allocateComplexMatrix (int linhas, int colunas)
{
    Complexo** matrix;
    //alocação de memória para o número de linhas
    matrix = (Complexo **) malloc(linhas*sizeof(Complexo*));

    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para elementos de cada linha da matriz
    for (int i = 0; i < colunas; i++)
    {
        matrix[i] = (Complexo *) malloc(colunas*sizeof(Complexo));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    return matrix;
}

void printComplex(Complexo z)
{
    printf("%+.2f %+.2fj", z.real, z.img);
}



