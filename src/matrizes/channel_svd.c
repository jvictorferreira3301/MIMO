#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <gsl/gsl_linalg.h>
#include <time.h>

void channel_svd(complexo **H, complexo **Uh, complexo **Sh, complexo **Vh, int linhas, int colunas){
    for (int l = 0; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			if (H[l][c].img != 0){
				printf("Warning: complex matrix injected as parameter, fuction will use only real part from matrix\n");
				break;
			}
		}
	}
    gsl_matrix * U = gsl_matrix_alloc(linhas, colunas); // Matriz U lxc
    gsl_matrix * V = gsl_matrix_alloc(colunas, colunas); // Matriz V cxc
    gsl_vector * S = gsl_vector_alloc(colunas); // Vetor S cx1
    gsl_vector * work = gsl_vector_alloc(colunas);
    
    for(int l=0; l<linhas; l++)
	{
        for(int c=0; c<colunas; c++)
		{
            printf("%+.1f ", H[l][c].real);
            gsl_matrix_set(U, l, c, H[l][c].real);
        }
        printf("\n");
    }
    gsl_linalg_SV_decomp(U, V, S, work);
    printf("\nMatriz U\n");
    for(int l=0; l<linhas; l++)
	{
        for(int c=0; c<colunas; c++)
		{
            printf("%f ", gsl_matrix_get(U, l, c));
        }
        printf("\n");
    }

    printf("\nVetor S\n");
    for(int c=0;c<colunas;c++)
	{
        printf("%f", gsl_vector_get(S,c));
        printf("\n");
    }

    printf("\nMatriz V\n");
    for(int l=0; l<colunas; l++)
	{
        for(int c=0; c<colunas; c++)
		{
            printf("%f ", gsl_matrix_get(V, l, c));
        }
        printf("\n");
    }
    //Matriz S de T a partir do vetor C.
    complexo** mtx_C = allocateComplexMatrix(colunas, colunas);
    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < colunas; c++){
            if (l == c){
                mtx_C[l][c].real = gsl_vector_get(S,l);
                mtx_C[l][c].img = 0;
            }else{
                mtx_C[l][c].real = 0;
                mtx_C[l][c].img = 0;
            }
        }
    }
    printf("\nmtx_C\n");
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(mtx_C[l][c]);
        }
        printf("\n");
    }

    complexo** Strans = transposta(mtx_C, colunas, colunas);
    printf("\nStrans\n");
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(Strans[l][c]);
        }
        printf("\n");
    }

    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < colunas; c++){
            Sh[l][c].real = Strans[l][c].real;
            Sh[l][c].img = Strans[l][c].img;
        }
    }

    printf("\nMatriz S de H\n");
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(Sh[l][c]);
        }
        printf("\n");
    }

    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < colunas; c++){
            Uh[l][c].real = gsl_matrix_get(V,l,c);
            Uh[l][c].img = 0;
        }
    }
    printf("\nMatriz U de H\n");
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(Uh[l][c]);
        }
        printf("\n");
    }
}

int main(){
    complexo** H;
    int linhas = 2;
    int colunas = 3;
    printf("linhas : %d\ncolunas: %d\n", linhas, colunas);
    H = allocateComplexMatrix(linhas, colunas);
    int n = 1;
    for (int l = 0; l < linhas; l++){
        for (int c = 0; c < colunas; c++){
            H[l][c].real = n;
            H[l][c].img = 0;
            n++;
        }
    }
    printf("\nCanalH:\n");
	for (int l = 0; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(H[l][c]);
		}
		printf("\n");
	}
    printf("\nAlocando USV...\n");
    complexo** U = allocateComplexMatrix(linhas, linhas);
    complexo** S = allocateComplexMatrix(linhas, linhas);
    complexo** V = allocateComplexMatrix(linhas, colunas);

    printf("Alocando T...\n");
    complexo ** T;
    T = transposta(H, linhas, colunas);
    int Tlinhas = colunas; int Tcolunas = linhas; 
    for (int l =0 ; l < Tlinhas; l++){
		for (int c = 0; c < Tcolunas; c++){
			printComplex(T[l][c]);
		}
        printf("\n");
	}
    printf("Transposição concluida!\n");
    printf("\nIniciando cálculo SVD de T..\n");
    printf("Passando dimensão: %d x %d\n", Tlinhas, Tcolunas);
    channel_svd(T, U, S, V, Tlinhas, Tcolunas);
    return 0;
}

