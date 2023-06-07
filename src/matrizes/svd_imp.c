#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <gsl/gsl_linalg.h>

void calc_svd(complexo** mtx, int linhas, int colunas);

int main()
{
    int linhas = 4;
    int colunas = 3;
    complexo** mtx;

    mtx = allocateComplexMatrix(linhas, colunas);

    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            mtx[l][c].real = 1 + l + c;
            mtx[l][c].img = 0;
        }
    }

    calc_svd(mtx, linhas, colunas);

    return 0;
}

void calc_svd(complexo** mtx, int linhas, int colunas)
{
    gsl_matrix * A = gsl_matrix_alloc(linhas, colunas);
    gsl_matrix * V = gsl_matrix_alloc(colunas, colunas);
    gsl_vector * S = gsl_vector_alloc(colunas);
    gsl_vector * work = gsl_vector_alloc(colunas);

    printf("Matriz A\n");
    for(int l=0; l<linhas; l++){
        for(int c=0; c<colunas; c++){
            printf("%f ", mtx[l][c].real);
            gsl_matrix_set(A, l, c, mtx[l][c].real);
        }
        printf("\n");
    }

    gsl_linalg_SV_decomp(A, V, S, work);

    printf("\n\nMatriz V\n");
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++){
            printf("%f ", gsl_matrix_get(V, l, c));
        }
        printf("\n");
    }


    printf("\n\nMatriz U\n");
    for(int l=0; l<linhas; l++){
        for(int c=0; c<colunas; c++){
            printf("%f ", gsl_matrix_get(A, l, c));
        }
        printf("\n");
    }

    printf("\n\nVetor S\n");
    for(int c=0;c<colunas;c++){
        printf("%f", gsl_vector_get(S,c));
        printf("\n");
    }
}