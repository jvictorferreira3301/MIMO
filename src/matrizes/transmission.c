#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <gsl/gsl_linalg.h>
#include <time.h>
complexo** produto_matricial_geral(complexo** mtx_a, complexo** mtx_b, int linhas_a, int colunas_a, int linhas_b, int colunas_b)
{
    // Validação da operação de multiplicação (colunas_a == linhas_b).
    if (colunas_a != linhas_b)
    {
        printf("\nErro: O produto não pode ser realizado (incompatibilidade entre matrizes)\n");
        exit(1);
    }
    
    complexo** matriz;
    matriz = allocateComplexMatrix(linhas_a, colunas_b);
    
    for (int l = 0; l < linhas_a; l++){
        for (int c = 0; c < colunas_b; c++){
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

complexo ** tx_precoder(complexo ** V, complexo **x, int Vlinhas, int Vcolunas, int xlinhas, int xcolunas){
    complexo **xp = produto_matricial_geral(V, x, Vlinhas, Vcolunas, xlinhas, xcolunas);
    return xp;
}

complexo ** channel_transmission(complexo ** H, complexo ** xp, int Hlinhas, int Hcolunas, int xpLinhas, int xpColunas, int r){
    complexo **xh = produto_matricial_geral(H, xp, Hlinhas, Hcolunas, xpLinhas, xpColunas);
    complexo ** Rd;
    if (r == 0){
        Rd = channel_rd_gen(Hlinhas, xpColunas, 0, 0);
    }else if (r == 1){
        Rd = channel_rd_gen(Hlinhas, xpColunas, -1, 1);
    }else if (r == 2){
        Rd = channel_rd_gen(Hlinhas, xpColunas, -0.5, 0.5);
    }else if (r == 3){
        Rd = channel_rd_gen(Hlinhas, xpColunas, -0.1, 0.1);
    }
    complexo ** xt = soma(xh, Rd, Hlinhas, xpColunas);
    printf("\nVetor Ruído\n");
    for (int l = 0 ; l < Hlinhas; l++){
		printComplex(Rd[l][0]);
        printf("\n");
	}
    return xt;
}

complexo ** rx_combiner(complexo ** U, complexo ** xt, int Ulinhas, int Ucolunas, int xtLinhas, int xtColunas){
    complexo ** xc = produto_matricial_geral(transposta(U, Ulinhas, Ucolunas), xt, Ucolunas, Ulinhas, xtLinhas, xtColunas);
    return xc;
}

complexo ** rx_feq(complexo ** S, complexo ** xc, int Slinhas, int Scolunas, int xcLinhas, int xcColunas){
    complexo ** xf = allocateComplexMatrix(xcLinhas, xcColunas);
    for (int l = 0; l < Slinhas; l++){
        for (int c = 0; c < Scolunas; c++){
            if (l == c){
                xf[l][0].real = xc[l][0].real/S[l][c].real;
                xf[l][0].img = xc[l][0].img/S[l][c].real;
            }
        }
    }
    return xf;
}

int main(){
    printf("\nDefinindo dimensões..\n");
    int Nr = 2, Nt = 4;
    int Nstream;
    int r = 3;
    if (Nr < Nt){
        Nstream = Nr;
    }else if (Nr >= Nt){
        Nstream = Nt;
    }
    printf("\nGerando canal H");
    complexo ** H = channel_gen(Nr, Nt, -1, 1);
    printf("\nTranspondo..");
    complexo ** T = transposta(H, Nr, Nt);
    printf("\nAlocando USV");
    complexo ** U = allocateComplexMatrix(Nr, Nr);
    complexo ** S = allocateComplexMatrix(Nr, Nr);
    complexo ** V = allocateComplexMatrix(Nt, Nr);
    printf("\nCalculando SVD de T\n");
    transposed_channel_svd(T, V, S, U, Nt, Nr);
    complexo ** x = allocateComplexMatrix(Nstream, 1);
    x[0][0].real = -1;
    x[0][0].img = 1;
    x[1][0].real = 1;
    x[1][0].img = -1;
    complexo ** xp = tx_precoder(V, x, Nt, Nr, Nstream, 1);
    printf("\nPrecoder...\n");
    for (int l = 0 ; l < Nt; l++){
		printComplex(xp[l][0]);
        printf("\n");
	}
    complexo ** xt = channel_transmission(H, xp, Nr, Nt, Nt, 1, r);
    //Talvez free(xp)
    printf("\nTransmission...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(xt[l][0]);
        printf("\n");
	}
    complexo ** xc = rx_combiner(U, xt, Nr, Nr, Nstream, 1);
    //Talvez free(xt);
    printf("\nCombiner...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(xc[l][0]);
        printf("\n");
	}
    printf("Equalização de sinal..\n");
    complexo ** xf = rx_feq(S, xc, Nr, Nr, Nstream, 1);
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(x[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(xf[l][0]);
        printf("\n");
	}
    Nr = 4; Nt = 2;
    if (Nr < Nt){
        Nstream = Nr;
    }else if (Nr >= Nt){
        Nstream = Nt;
    }
    printf("\nGerando canal L");
    complexo ** L = channel_gen(Nr, Nt, -1, 1);
    printf("\nAlocando USV");
    complexo ** Ul = allocateComplexMatrix(Nr, Nt);
    complexo ** Sl = allocateComplexMatrix(Nt, Nt);
    complexo ** Vl = allocateComplexMatrix(Nt, Nt);
    printf("\nCalculando SVD de L\n");
    square_channel_svd(L, Ul, Sl, Vl, Nr, Nt);
    complexo ** y = allocateComplexMatrix(Nstream, 1);
    y[0][0].real = -1;
    y[0][0].img = 1;
    y[1][0].real = 1;
    y[1][0].img = -1;
    printf("\nVetor y...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(y[l][0]);
        printf("\n");
	}
    complexo ** yp = tx_precoder(Vl, y, Nt, Nt, Nstream, 1);
    printf("\nPrecoder...\n");
    for (int l = 0 ; l < Nstream; l++){ // Nt == Nstream
		printComplex(yp[l][0]);
        printf("\n");
	}
    printf("\nTransmission...\n");
    complexo ** yt = channel_transmission(L, yp, Nr, Nt, Nstream, 1, r);
    printf("\ncu\n");
    for (int l = 0 ; l < Nr; l++){
		printComplex(yt[l][0]);
        printf("\n");
	}
    complexo ** yc = rx_combiner(Ul, yt, Nr, Nt, Nr, 1);
    printf("\nCombiner...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(yc[l][0]);
        printf("\n");
	}
    printf("Equalização de sinal..\n");
    complexo ** yf = rx_feq(Sl, yc, Nt, Nt, Nstream, 1);
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(y[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(yf[l][0]);
        printf("\n");
	}
    Nt = 4;
    if (Nr < Nt){
        Nstream = Nr;
    }else if (Nr >= Nt){
        Nstream = Nt;
    }
    printf("\nGerando canal L");
    complexo ** Q = channel_gen(Nr, Nt, -1, 1);
    printf("\nAlocando USV");
    complexo ** Uq = allocateComplexMatrix(Nr, Nt);
    complexo ** Sq = allocateComplexMatrix(Nt, Nt);
    complexo ** Vq = allocateComplexMatrix(Nt, Nt);
    printf("\nCalculando SVD de L\n");
    square_channel_svd(Q, Uq, Sq, Vq, Nr, Nt);
    complexo ** z = allocateComplexMatrix(Nstream, 1);
    z[0][0].real = -1;
    z[0][0].img = 1;
    z[1][0].real = 1;
    z[1][0].img = -1;
    z[2][0].real = -1;
    z[2][0].img = 1;
    z[3][0].real = 1;
    z[3][0].img = -1;
    printf("\nVetor z...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(z[l][0]);
        printf("\n");
	}
    complexo ** zp = tx_precoder(Vq, z, Nt, Nt, Nstream, 1);
    printf("\nPrecoder...\n");
    for (int l = 0 ; l < Nstream; l++){ // Nt == Nstream
		printComplex(zp[l][0]);
        printf("\n");
	}
    printf("\nTransmission...\n");
    complexo ** zt = channel_transmission(Q, zp, Nr, Nt, Nstream, 1, r);
    printf("\ncu\n");
    for (int l = 0 ; l < Nr; l++){
		printComplex(zt[l][0]);
        printf("\n");
	}
    complexo ** zc = rx_combiner(Uq, zt, Nr, Nt, Nr, 1);
    printf("\nCombiner...\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(zc[l][0]);
        printf("\n");
	}
    printf("Equalização de sinal..\n");
    complexo ** zf = rx_feq(Sq, zc, Nt, Nt, Nstream, 1);
    printf("\nVetor transmitido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(z[l][0]);
        printf("\n");
	}
    printf("\nVetor recebido\n");
    for (int l = 0 ; l < Nstream; l++){
		printComplex(zf[l][0]);
        printf("\n");
	}
    return 0;
}