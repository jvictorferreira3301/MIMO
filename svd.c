#include <stdlib.h>
#include <gsl/gsl_linalg.h>


int main(){
    #define i 5
    #define j 4
    int l,c;
    double a_data[i][j];
    for (l=0; l<i;l++){
        for(c=0; c<j; c++){
            a_data[l][c] = l+ 2*c;  
        }
    }

    gsl_matrix * A = gsl_matrix_alloc(i,j); 
    gsl_matrix * V = gsl_matrix_alloc(j,j);
    gsl_vector * S = gsl_vector_alloc(j);
    gsl_vector * work = gsl_vector_alloc(j);

    printf("Matriz A\n");
    for(l=0; l<i; l++){
        for(c=0; c<j; c++){
            printf("%f ", a_data[l][c]);
            gsl_matrix_set(A, l, c, a_data[l][c]);
        }
        printf("\n");
    }

    gsl_linalg_SV_decomp(A, V, S, work);

    printf("\n\nMatriz V\n");
    for(l=0; l<j; l++){
        for(c=0; c<j; c++){
            printf("%f ", gsl_matrix_get(V, c, l));
        }
        printf("\n");
    }


    printf("\n\nMatriz U\n");
    for(l=0; l<i; l++){
        for(c=0; c<j; c++){
            printf("%f ", gsl_matrix_get(A, l, c));
        }
        printf("\n");
    }

    printf("\n\nVetor S\n");
    for(c=0;c<j;c++){
        printf("%f", gsl_vector_get(S,c));
        printf("\n");
    }
    return 0;
}