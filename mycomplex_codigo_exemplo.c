#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float real, img;
}Complexo;

void printComplex(Complexo z)
{
    printf("%+f %+f\n", z.real, z.img);
}

Complexo** allocateComplexMatrix (int linhas, int colunas)
{
    Complexo** matrix;

    matrix = (Complexo **) malloc(linhas*sizeof(int));

    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para cada linha da matriz
    for (int i = 0; i < colunas; i++)
    {
        matrix[i] = (int *) malloc(colunas*sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    return matrix;
}

void main()
{
    Complexo** mtx;

    int nlinhas = 2;
    int ncolunas = 3;

    mtx = allocateComplexMatrix(nlinhas, ncolunas);

    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
            mtx[l][c].real = 2*1;
            mtx[l][c].img = 2*c;
        }
    }

    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
         {
            printf("mtx[%d][%d]: ",l,c);
            printComplex(mtx[l][c]);
        }
    }
}