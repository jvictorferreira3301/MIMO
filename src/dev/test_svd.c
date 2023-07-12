#include <stdio.h>
#include <gsl/gsl_linalg.h>
void main (void){
    #define M 3
    #define N 2
    double a_data[M][N];
    a_data[0][0] = 1; a_data[0][1] = 4; 
    a_data[1][0] = 2; a_data[1][1] = 5; 
    a_data[2][0] = 3; a_data[2][1] = 6;

    gsl_matrix * A = gsl_matrix_alloc(M, N);
    gsl_matrix * V = gsl_matrix_alloc(N, N);
    gsl_vector * S = gsl_vector_alloc(N);
    gsl_vector * work = gsl_vector_alloc(N);
    int i,j;
    printf("Matriz A\n");
    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
        printf("%f ", a_data[i][j]);
        gsl_matrix_set(A, i, j, a_data[i][j]);
        }
        printf("\n");
    }
    gsl_linalg_SV_decomp(A, V, S, work);
    printf("\n\nMatriz U\n");
    for(i=0; i<M; i++){
        for(j=0; j<N; j++){
        printf("%f ", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }
    printf("\n\nMatriz V\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
        printf("%f ", gsl_matrix_get(V, i, j));
        }
        printf("\n");
    }
    printf("\n\nVetor S\n");
    for(i=0; i<N; i++)
    printf("%f ", gsl_vector_get(S, i));
    printf("\n");
}