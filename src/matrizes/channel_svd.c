#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <gsl/gsl_linalg.h>
#include <time.h>
complexo** product_mtx(complexo** mtx_a, complexo** mtx_b, int linhas_a, int colunas_a, int linhas_b, int colunas_b)
{
    // Validação da operação de multiplicação (colunas_a == linhas_b).
    if (colunas_a != linhas_b)
    {
        printf("\nErro: O produto não pode ser realizado (incompatibilidade entre matrizes)\n");
        exit(1);
    }
    
    complexo** matriz;
    matriz = allocateComplexMatrix(linhas_a, colunas_b);
    
    for (int l = 0; l < linhas_a; l++)
    {
        for (int c = 0; c < colunas_b; c++)
        {
            complexo acumulador;
            acumulador.real = 0;
            acumulador.img = 0;
            
            for (int i = 0; i < colunas_a; i++)
            {
                acumulador = soma_complexo(acumulador, multcomp(mtx_a[l][i], mtx_b[i][c]));
            }
            
            matriz[l][c].real = acumulador.real;
            matriz[l][c].img = acumulador.img;
        }
    }
    
    return matriz;
}

complexo ** channel_rd_gen(int Nr, int Nt, float minValue, float maxValue){
    complexo** H;
	
    H = (complexo **) malloc(Nr*sizeof(complexo*));
	
    if (H == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //Alocação de memória para cada linha da matriz
    for (int i = 0; i < Nr; i++)
    {
        H[i] = (complexo *) malloc(Nt*sizeof(complexo));
        if (H[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    srand(time(NULL));
    for (int i = 0; i < Nr; i++) {
        for (int j = 0; j < Nt; j++) {
            H[i][j].real = ((double)rand() / RAND_MAX) * (maxValue - minValue) + minValue;
            H[i][j].img = ((double)rand() / RAND_MAX) * (maxValue - minValue) + minValue;
        }
    }
    return H;
}

void channel_svd(complexo **H, complexo **Uh, complexo **Sh, complexo **Vh, int Tlinhas, int Tcolunas){
    for (int l = 0; l < Tlinhas; l++){
		for (int c = 0; c < Tcolunas; c++){
			if (H[l][c].img != 0){
				printf("Warning: complex matrix injected as parameter, fuction will use only real part from matrix\n");
				break;
			}
		}
	}
    gsl_matrix * U = gsl_matrix_alloc(Tlinhas, Tcolunas); // Matriz U lxc
    gsl_matrix * V = gsl_matrix_alloc(Tcolunas, Tcolunas); // Matriz V cxc
    gsl_vector * S = gsl_vector_alloc(Tcolunas); // Vetor S cx1
    gsl_vector * work = gsl_vector_alloc(Tcolunas);
    
    for(int l=0; l<Tlinhas; l++)
	{
        for(int c=0; c<Tcolunas; c++)
		{
            printf("%+.1f ", H[l][c].real);
            gsl_matrix_set(U, l, c, H[l][c].real);
        }
        printf("\n");
    }

    gsl_linalg_SV_decomp(U, V, S, work);
    printf("\nMatriz U que vira Vh\n");
    for(int l=0; l<Tlinhas; l++)
	{
        for(int c=0; c<Tcolunas; c++)
		{
            Uh[l][c].real = gsl_matrix_get(U, l, c);
            Uh[l][c].img = 0;
            printf("%f ", gsl_matrix_get(U, l, c));
        }
        printf("\n");
    }

    printf("\nVetor S\n");
    for(int c=0;c<Tcolunas;c++)
	{
        printf("%f", gsl_vector_get(S,c));
        printf("\n");
    }

    printf("\nMatriz V que vira Uh\n");
    for(int l=0; l<Tcolunas; l++)
	{
        for(int c=0; c<Tcolunas; c++)
		{
            Vh[l][c].real = gsl_matrix_get(V, l, c);
            Vh[l][c].img = 0;
            printf("%f ", gsl_matrix_get(V, l, c));
        }
        printf("\n");
    }
    //Matriz S de T a partir do vetor C.
    for (int l = 0; l < Tcolunas; l++){
        for (int c = 0; c < Tcolunas; c++){
            if (l == c){
                Sh[l][c].real = gsl_vector_get(S,c);
                Sh[l][c].img = 0;
            }else{
                Sh[l][c].real = 0;
                Sh[l][c].img = 0;
            }
        }
    }
    printf("\nMatriz diagonal S\n");
    for(int l=0; l<Tcolunas; l++){
        for(int c=0; c<Tcolunas; c++)
		{
            printComplex(Sh[l][c]);
        }
        printf("\n");
    }
}

void square_channel_svd(complexo **H, complexo**Uh, complexo**Sh, complexo**Vh, int linhas, int colunas){
    for (int l = 0; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			if (H[l][c].img != 0){
				printf("Warning: complex matrix injected as parameter, fuction will use only real part from matrix\n");
				break;
			}
		}
	}
    gsl_matrix * U = gsl_matrix_alloc(linhas, colunas); // Matriz U lxc
    gsl_matrix * V = gsl_matrix_alloc(linhas, colunas); // Matriz V cxc
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
    for(int l = 0; l < linhas; l++)
	{
        for(int c=0; c < colunas; c++)
		{
            Uh[l][c].real = gsl_matrix_get(U, l, c);
            Uh[l][c].img = 0;
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
    for(int l=0; l<linhas; l++)
	{
        for(int c=0; c<colunas; c++)
		{
            Vh[l][c].real = gsl_matrix_get(V, l, c);
            Vh[l][c].img = 0;
            printf("%f ", gsl_matrix_get(V, l, c));
        }
        printf("\n");
    }

    printf("\nMatriz diagonal S\n");
    for (int l = 0; l < linhas; l++){
        for (int c = 0; c < colunas; c++){
            if (l == c){
                Sh[l][c].real = gsl_vector_get(S,c);
                Sh[l][c].img = 0;
            }else{
                Sh[l][c].real = 0;
                Sh[l][c].img = 0;
            }
        }
    }
    for(int l=0; l<linhas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(Sh[l][c]);
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
    complexo** V = allocateComplexMatrix(colunas, linhas);
    complexo** vector_S = allocateComplexMatrix(linhas, 1);

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
    complexo** p = product_mtx(H, T, linhas, colunas, Tlinhas, Tcolunas);
    printf("\nIniciando cálculo SVD de T..\n");
    printf("Passando dimensão: %d x %d\n", Tlinhas, Tcolunas);
    channel_svd(T, V, S, U, Tlinhas, Tcolunas);
    printf("\nVoltando ao programa principal...\n");
    printf("\nMatriz U\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(U[l][c]);
		}
        printf("\n");
	}
    printf("\nMatriz S diagonal\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(S[l][c]);
		}
        printf("\n");
	}
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			if(l == c){
                vector_S[l][0].real = S[l][c].real;
                vector_S[l][0].img = S[l][c].img;
            }
		}
        printf("\n");
	}
    printf("\nMatriz V\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(V[l][c]);
		}
        printf("\n");
	}
    printf("\nIniciando teste de vida ou morte... (°-°)\n");
    complexo ** us = product_mtx(U, S, linhas, linhas, linhas, linhas);
    complexo ** vt = transposta(V, colunas, linhas);
    complexo ** usvt = product_mtx(us, vt, linhas, linhas, linhas, colunas);
    printf("\nMultiplicação U*S\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(us[l][c]);
		}
        printf("\n");
	}
    printf("\nTransposta Vt\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(vt[l][c]);
		}
        printf("\n");
	}
    printf("\nSuposta matriz Canal H vindo do SVD...\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(usvt[l][c]);
		}
        printf("\n");
	}
    complexo ** x = allocateComplexMatrix(linhas, 1);
    x[0][0].real = 1; 
    x[0][0].img = 1;
    x[1][0].real = -1; 
    x[1][0].img = -1;
    //x[2][0].real = 1;
    //x[2][0].img = -1;
    printf("\nPrecoder...\n");
    complexo **xp = product_mtx(V, x, colunas, linhas, linhas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(xp[l][0]);
        printf("\n");
	}
    printf("\nChannel transmission...\n");
    printf("Matriz H...\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(usvt[l][c]);
		}
        printf("\n");
	}
    complexo **Rd;
    Rd=channel_rd_gen(linhas,1,-1,1);
    printf("Vetor Ruído\n");
        for (int l = 0 ; l < linhas; l++){
		    printComplex(Rd[l][0]);
            printf("\n");
	    }
    printf("\nMultiplicação pelo canal H..\n");
    complexo **xh = product_mtx(H, xp, linhas, colunas, colunas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(xh[l][0]);
        printf("\n");
	}
    printf("\nSoma com o ruído Rd...\n");
    complexo ** xc = soma(xh, Rd, linhas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(xc[l][0]);
        printf("\n");
	}
    printf("Saindo do canal..");
    printf("\nCombiner...\n");
    complexo **xcomb = product_mtx(transposta(U, linhas, linhas), xc, linhas, linhas, linhas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(xcomb[l][0]);
        printf("\n");
	}
    printf("\nEqualização de canal...");
    printf("\nVetor S\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(vector_S[l][0]);
        printf("\n");
	}
    complexo ** xf = allocateComplexMatrix(linhas, 1);
    for (int l = 0; l < linhas; l++){
        xf[l][0].real = xcomb[l][0].real/vector_S[l][0].real;
        xf[l][0].img = xcomb[l][0].img/vector_S[l][0].real; 
    }
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(x[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(xf[l][0]);
        printf("\n");
	}
    printf("\n");
    printf("\n Iniciando teste de transmissão utilizando matriz e canal H quadrada...\n");
    complexo** Q = allocateComplexMatrix(colunas, colunas);
    n = 1;
    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < colunas; c++){
            Q[l][c].real = n;
            Q[l][c].img = 0;
            n++;
        }
    }
    printf("\nCanalH:\n");
	for (int l = 0; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(Q[l][c]);
		}
		printf("\n");
	}
    printf("\nAlocando USV para Q...\n");
    complexo** Uq = allocateComplexMatrix(colunas, colunas);
    complexo** Sq = allocateComplexMatrix(colunas, colunas);
    complexo** Vq = allocateComplexMatrix(colunas, colunas);
    complexo** vector_Sq = allocateComplexMatrix(colunas, 1);
    printf("\nIniciando SVD de Q...\n");
    square_channel_svd(Q, Uq, Sq, Vq, colunas, colunas);
    printf("\nImprimindo as matrizes Uq, Sq e Vq");
    printf("\nMatriz Uq\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(Uq[l][c]);
		}
        printf("\n");
	}
    printf("\nMatriz S diagonal\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(Sq[l][c]);
		}
        printf("\n");
	}
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			if(l == c){
                vector_Sq[l][0].real = Sq[l][c].real;
                vector_Sq[l][0].img = Sq[l][c].img;
            }
		}
	}
    printf("\nMatriz Vq\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(Vq[l][c]);
		}
        printf("\n");
	}
    printf("\nIniciando teste de vida ou morte 2... (°-°)\n");
    complexo ** usq = product_mtx(Uq, Sq, colunas, colunas, colunas, colunas);
    complexo ** vqt = transposta(Vq, colunas, colunas);
    complexo ** usvtq = product_mtx(usq, vqt, colunas, colunas, colunas, colunas);
    printf("\nSuposta matriz Canal Q vindo do SVD...\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(usvtq[l][c]);
		}
        printf("\n");
	}

    return 0;
}