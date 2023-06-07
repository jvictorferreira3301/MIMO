#include <stdio.h>
#include <stdlib.h>
#include "./matrizes/matrizes.h"
#include <gsl/gsl_linalg.h>
 
#define M = linhas
#define N = colunas

int main()
{
    int linhas = 4
    int colunas = 3
    complexo** mtx;

    mtx = allocateComplexMatrix(linhas, colunas);

    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            mtx[l][c].real = 1 + l + c;
            mtx[l][c].img = 1 + l - c;
        }
    }

    calc_svd(mtx, linhas, colunas);

    return 0;
}

void calc_svd(complexo** mtx, int linhas, int colunas)
{
    gsl_matrix * A = gsl_matrix_alloc(M, N);
    gsl_matrix * V = gsl_matrix_alloc(N, N);
    gsl_vector * S = gsl_vector_alloc(N);
    gsl_vector * work = gsl_vector_alloc(N);

    for (int l = 0; l < M)
}