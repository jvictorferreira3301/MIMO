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

complexo ** channel_gen(int Nr, int Nt, float minValue, float maxValue){
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
        }
    }
    return H;
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

void transposed_channel_svd(complexo **H, complexo **Uh, complexo **Sh, complexo **Vh, int Tlinhas, int Tcolunas){
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
    for(int l=0; l<colunas; l++)
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
    for (int l = 0; l < colunas; l++){
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
    for(int l=0; l<colunas; l++){
        for(int c=0; c<colunas; c++)
		{
            printComplex(Sh[l][c]);
        }
        printf("\n");
    }
}

int main(){
    int linhas = 2;
    int colunas = 4;
    printf("linhas : %d\ncolunas: %d\n", linhas, colunas);
    complexo** H = channel_gen(linhas, colunas, -1, 1);
    /*H = allocateComplexMatrix(linhas, colunas);
    int n = 1;
    for (int l = 0; l < linhas; l++){
        for (int c = 0; c < colunas; c++){
            H[l][c].real = n;
            H[l][c].img = 0;
            n++;
        }
    }*/
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
    printf("\nIniciando cálculo SVD de T..\n");
    printf("Passando dimensão: %d x %d\n", Tlinhas, Tcolunas);
    transposed_channel_svd(T, V, S, U, Tlinhas, Tcolunas);
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
    Rd=channel_rd_gen(linhas,1,-0,0);
    printf("\nMultiplicação pelo canal H..\n");
    complexo **xh = product_mtx(H, xp, linhas, colunas, colunas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(xh[l][0]);
        printf("\n");
	}
    printf("Vetor Ruído\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(Rd[l][0]);
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
    printf("\n Iniciando teste de transmissão utilizando matriz e canal Q quadrada...\n");
    complexo** Q = channel_gen(colunas, colunas, -1, 1);
    /*n = 1;
    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < colunas; c++){
            Q[l][c].real = n;
            Q[l][c].img = 0;
            n++;
        }
    }*/
    printf("\nCanal Q:\n");
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
    printf("\nMatriz Sq diagonal\n");
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
    printf("\nIniciando transmissão de y pelo canal Q...\n");
    complexo ** y = allocateComplexMatrix(colunas, 1);
    y[0][0].real = 1; 
    y[0][0].img = 1;
    y[1][0].real = -1; 
    y[1][0].img = -1;
    y[2][0].real = 1;
    y[2][0].img = -1;
    printf("\nVetor y\n");
    for (int l = 0 ; l < colunas; l++){
		printComplex(y[l][0]);
        printf("\n");
	}
    printf("\nPrecoder...\n");
    complexo **yp = product_mtx(Vq, y, colunas, colunas, colunas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(yp[l][0]);
        printf("\n");
	}
    printf("\nChannel transmission by Q...\n");
    printf("Matriz Q...\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < colunas; c++){
			printComplex(usvtq[l][c]);
		}
        printf("\n");
	}
    complexo **Rdq;
    Rdq=channel_rd_gen(colunas,1,-0.5,0.5);
    printf("\nMultiplicação pelo canal H..\n");
    complexo **yh = product_mtx(Q, yp, colunas, colunas, colunas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(yh[l][0]);
        printf("\n");
	}
    printf("\nVetor Ruído em Q\n");
        for (int l = 0 ; l < colunas; l++){
		    printComplex(Rdq[l][0]);
            printf("\n");
	    }
    printf("\nSoma com o ruído Rdq...\n");
    complexo ** yc = soma(yh, Rdq, colunas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(yc[l][0]);
        printf("\n");
	}
    printf("\nSaindo do canal..");
    printf("\nCombiner...\n");
    complexo **ycomb = product_mtx(transposta(Uq, colunas, colunas), yc, colunas, colunas, colunas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(ycomb[l][0]);
        printf("\n");
	}
    printf("\nEqualização de canal...");
    printf("\nVetor Sq\n");
    for (int l = 0 ; l < colunas; l++){
		printComplex(vector_Sq[l][0]);
        printf("\n");
	}
    complexo ** yf = allocateComplexMatrix(colunas, 1);
    for (int l = 0; l < colunas; l++){
        yf[l][0].real = ycomb[l][0].real/vector_Sq[l][0].real;
        yf[l][0].img = ycomb[l][0].img/vector_Sq[l][0].real; 
    }
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < colunas; l++){
		printComplex(y[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < colunas; l++){
		printComplex(yf[l][0]);
        printf("\n");
	}
    printf("\nIniciando teste de compatibilidade de square_channel_svd para matrizes onde linhas > colunas");
    complexo ** L = channel_gen(colunas, linhas, -1, 1);
    /*n = 1;
    for (int l = 0; l < colunas; l++){
        for (int c = 0; c < linhas; c++){
            L[l][c].real = n;
            L[l][c].img = 0;
            n++;
        }
    }*/
    printf("\nCanal L:\n");
	for (int l = 0; l < colunas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(L[l][c]);
		}
		printf("\n");
	}
    printf("\nAlocando USV para L...\n");
    complexo** Ul = allocateComplexMatrix(colunas, linhas);
    complexo** Sl = allocateComplexMatrix(linhas, linhas);
    complexo** Vl = allocateComplexMatrix(linhas, linhas);
    complexo** vector_Sl = allocateComplexMatrix(linhas, 1);
    printf("\nIniciando SVD de L...\n");
    square_channel_svd(L, Ul, Sl, Vl, colunas, linhas);
    printf("\nImprimindo as matrizes Ul, Sl e Vl");
    printf("\nMatriz Ul\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(Ul[l][c]);
		}
        printf("\n");
	}
    printf("\nMatriz Sl diagonal\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(Sl[l][c]);
		}
        printf("\n");
	}
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			if(l == c){
                vector_Sl[l][0].real = Sl[l][c].real;
                vector_Sl[l][0].img = Sl[l][c].img;
            }
		}
	}
    printf("\nMatriz Vl\n");
    for (int l =0 ; l < linhas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(Vl[l][c]);
		}
        printf("\n");
	}
    printf("\nIniciando teste de vida ou morte 3... (°-°)\n");
    complexo ** usl = product_mtx(Ul, Sl, colunas, linhas, linhas, linhas);
    complexo ** vlt = transposta(Vl, linhas, linhas);
    complexo ** usvtl = product_mtx(usl, vlt, colunas, linhas, linhas, linhas);
    printf("\nSuposta matriz Canal L vindo do SVD...\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(usvtl[l][c]);
		}
        printf("\n");
	}
    printf("\nIniciando transmissão de y pelo canal L...\n");
    complexo ** z = allocateComplexMatrix(linhas, 1);
    z[0][0].real = 1; 
    z[0][0].img = 1;
    z[1][0].real = -1; 
    z[1][0].img = -1;
    printf("\nVetor z\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(z[l][0]);
        printf("\n");
	}
    printf("\nPrecoder...\n");
    complexo **zp = product_mtx(Vl, z, linhas, linhas, linhas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(zp[l][0]);
        printf("\n");
	}
    printf("\nChannel transmission by L...\n");
    printf("Matriz L...\n");
    for (int l =0 ; l < colunas; l++){
		for (int c = 0; c < linhas; c++){
			printComplex(usvtl[l][c]);
		}
        printf("\n");
	}
    complexo **Rdl;
    Rdl=channel_rd_gen(colunas,1,-0.5,0.5);
    printf("\nMultiplicação pelo canal L..\n");
    complexo **zh = product_mtx(L, zp, colunas, linhas, linhas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(zh[l][0]);
        printf("\n");
	}
    printf("\nVetor Ruído em L\n");
        for (int l = 0 ; l < colunas; l++){
		    printComplex(Rdl[l][0]);
            printf("\n");
	    }
    printf("\nSoma com o ruído Rdl...\n");
    complexo ** zc = soma(zh, Rdq, colunas, 1);
    for (int l = 0 ; l < colunas; l++){
		printComplex(zc[l][0]);
        printf("\n");
	}
    printf("\nSaindo do canal..");
    printf("\nCombiner...\n");
    complexo **zcomb = product_mtx(transposta(Ul, colunas, linhas), zc, linhas, colunas, colunas, 1);
    for (int l = 0 ; l < linhas; l++){
		printComplex(zcomb[l][0]);
        printf("\n");
	}
    printf("\nEqualização de canal...");
    printf("\nVetor Sl\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(vector_Sl[l][0]);
        printf("\n");
	}
    complexo ** zf = allocateComplexMatrix(colunas, 1);
    for (int l = 0; l < linhas; l++){
        zf[l][0].real = zcomb[l][0].real/vector_Sl[l][0].real;
        zf[l][0].img = zcomb[l][0].img/vector_Sl[l][0].real; 
    }
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(z[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < linhas; l++){
		printComplex(zf[l][0]);
        printf("\n");
	}
    return 0;
}