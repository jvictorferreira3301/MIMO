#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

/* Alocação de memoria para uma matriz complexa*/
complexo** allocateComplexMatrix (int linhas, int colunas)
{
    complexo** matrix;
	

    matrix = (complexo **) malloc(linhas*sizeof(complexo*));
	
    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para cada linha da matriz
    for (int i = 0; i < linhas; i++)
    {
        matrix[i] = (complexo *) malloc(colunas*sizeof(complexo));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    return matrix;
}

/*Printa o complexo C*/
void printComplex(complexo c)
{
    printf("%+.2f %+.2fj ", c.real, c.img);
}

complexo soma_complexo(complexo c1, complexo c2)
{
	complexo soma;

	soma.real = c1.real + c2.real;
	soma.img = c1.img + c2.img;

	return soma;
}
/*Função que faz a matriz conjugada*/
complexo** conjugada(complexo **mtx, int linhas, int colunas) //Kauan (06.05.23)
{
    complexo ** matrix;
    //alocação da matriz 
    matrix = allocateComplexMatrix (linhas, colunas);

    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            matrix[l][c].real = mtx[l][c].real;
            matrix[l][c].img = -mtx[l][c].img;
        }
    }

    return matrix;
}

void teste_conjugada(void) //Kauan (06.05.23)
{
	complexo **mtx_a, **mtx_conj_a, **mtx_b, **mtx_conj_b, **mtx_c, **mtx_conj_c;

	int nlinhas = 3, ncolunas = 3;

	//Alocação de memória. 
	mtx_a = allocateComplexMatrix(nlinhas, ncolunas);
	mtx_b = allocateComplexMatrix(nlinhas, ncolunas);
	mtx_c = allocateComplexMatrix(nlinhas, ncolunas);

	//Preenchimento da(s) matriz(es).
	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			mtx_a[l][c].real = (1+l)*c;
			mtx_a[l][c].img = 4*l - 2*c;

			mtx_b[l][c].real = 2 + l +c; 
			mtx_b[l][c].img = l - 3*c;

			mtx_c[l][c].real = -2*l + 3*c;
			mtx_c[l][c].img = -l - 2*c;
		}
	}

	//Chamada da função conjugada.
	mtx_conj_a = conjugada(mtx_a, nlinhas, ncolunas);
	mtx_conj_b = conjugada(mtx_b, nlinhas, ncolunas);
	mtx_conj_c = conjugada(mtx_c, nlinhas, ncolunas);

	printf("\n=== Operando A ===\n");
	//Impressão da Matriz A.
	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_a[l][c]);
		}
		printf("\n");
	}
	
	printf("\n=== Operando B ===\n");
	//Impressão da Matriz B.
		for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_b[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Operando C ===\n");
	//Impressão da Matriz C.
		for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_c[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Resultado ===\n");
	//Impressão da(s) matriz(es) conjugada(s)
	printf("\n=== Conjugada de A ===\n");

	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_conj_a[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Conjugada de B ===\n");

		for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_conj_b[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Conjugada de C ===\n");

			for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_conj_c[l][c]);
		}
		printf("\n");
	}
	//Finalização do teste.
	printf("\n=== Fim do teste da função conjugada() ===\n");
}

/* a função que faz a transposta da matriz*/
complexo** transposta(complexo** matriz,int linhas, int colunas)
{
        complexo** mtx;

        mtx = allocateComplexMatrix(colunas,linhas);
        for (int l = 0; l < linhas; l++)
		{
			for (int c = 0; c < colunas; c++)
			{
				mtx[l][c].real = matriz[c][l].real;
                mtx[l][c].img = matriz[c][l].img;
			}
		}
    return mtx;
}

complexo** hermetiana(complexo** mtx, int linhas, int colunas)
{
    complexo **matriz, **matriz_h;

    matriz = allocateComplexMatrix(linhas, colunas);
    matriz_h = allocateComplexMatrix(linhas, colunas);

    matriz = conjugada(mtx, linhas, colunas);
    matriz_h = transposta(matriz, linhas, colunas);

    return matriz_h;
}

void teste_hermetiana(void)
{
    complexo **mtx_a, **mtx_a_h, **mtx_b, **mtx_b_h, **mtx_c, **mtx_c_h;

    int nlinhas =3, ncolunas = 3;
	//Alocação de memória.
    mtx_a = allocateComplexMatrix(nlinhas, ncolunas);
	mtx_b = allocateComplexMatrix(nlinhas, ncolunas);
	mtx_c = allocateComplexMatrix(nlinhas, ncolunas);
	//Preenchimento da(s) matriz(es).
    for (int l = 0; l < ncolunas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
			//Matriz A.
            mtx_a[l][c].real = l + c;
            mtx_a[l][c].img = l - 2*c;
			//Matriz B.
			mtx_b[l][c].real = 1 + l - 3*c;
			mtx_b[l][c].img = 2*l + 4 - c;
			//Matriz C.
			mtx_c[l][c].real = l - 3*c;
			mtx_c[l][c].img = 1 - l + 2*c;
        }
    }
	//Impressão da(s) matriz(es).
    printf("\n=== Operando A ===\n");

    for (int l = 0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_a[l][c]);
		}
        printf("\n");
	}

	printf("\n=== Operando B ===\n");

    for (int l = 0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_b[l][c]);
		}
        printf("\n");
	}

	printf("\n=== Operando C ===\n");

    for (int l = 0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_c[l][c]);
		}
        printf("\n");
	}
	//Chamada da função Hermetiana.
    mtx_a_h = hermetiana(mtx_a, nlinhas, ncolunas);
	mtx_b_h = hermetiana(mtx_b, nlinhas, ncolunas);
	mtx_c_h = hermetiana(mtx_c, nlinhas, ncolunas);

    int nlinhas_trans = ncolunas;
	int ncolunas_trans = nlinhas;

	//Impressão da(s) matriz(es) hermetianas.
	printf("\n=== Matriz Hermetiana de A ===\n");

    for (int l = 0 ; l < nlinhas_trans; l++)
	{
		for (int c = 0; c < ncolunas_trans; c++)
		{
			printComplex(mtx_a_h[l][c]);
		}
        printf("\n");
	}

	printf("\n=== Matriz Hermetiana de B ===\n");

    for (int l = 0 ; l < nlinhas_trans; l++)
	{
		for (int c = 0; c < ncolunas_trans; c++)
		{
			printComplex(mtx_b_h[l][c]);
		}
        printf("\n");
	}

	printf("\n=== Matriz Hermetiana de C ===\n");

    for (int l = 0 ; l < nlinhas_trans; l++)
	{
		for (int c = 0; c < ncolunas_trans; c++)
		{
			printComplex(mtx_c_h[l][c]);
		}
        printf("\n");
	}
	//Fim do teste da função Hermetiana.
}

/*Soma duas matrizes complexas*/
complexo** soma(complexo** c2, complexo** c1, int linhas, int colunas)
{
	complexo** matrix;
	
	matrix = allocateComplexMatrix(linhas,colunas);
		for (int l = 0; l < linhas; l++)
		{
			for (int c = 0; c < colunas; c++)
			{
				matrix[l][c].real = c1[l][c].real + c2[l][c].real;
                matrix[l][c].img = c1[l][c].img + c2[l][c].img;
			}
		}
	return matrix;
}

/*Subtrai duas matrizes complexas*/
complexo** subtracao(complexo** c1, complexo** c2, int linhas, int colunas)
{
	complexo** matrix;
	
	matrix = allocateComplexMatrix(linhas,colunas);
		for (int l = 0; l < linhas; l++)
		{
			for (int c = 0; c < colunas; c++)
			{
				matrix[l][c].real = c1[l][c].real - c2[l][c].real;
                matrix[l][c].img = c1[l][c].img - c2[l][c].img;
			}
		}
	return matrix;
}

/*Multiplicaçao de duas matrizes*/
complexo** produto_matricial(complexo** mtx_a, complexo **mtx_b, int linhas, int colunas)  //Kauan (07.05.23)
{
	//Validação da operação de multiplicação (colunas_a == linhas_b).
	if(linhas != colunas)
	{
		printf("\nErro: O produto não pode ser realizado (incompatibilidade entre matrizes)\n");
		exit(1);
	}
	//Declaração e alocação de memória.
	complexo** matriz;
	matriz = allocateComplexMatrix(linhas, colunas);
	//O número de linhas da matriz B - à direita - é usado como parâmento na função.
	int linhas_b = colunas;
	//Início da operação. Observer que é necessário um 'acumulador' para guardar o valor da soma dos produtos Aij x Bij que geram um termo Cij.
	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			complexo acumulador;
			acumulador.real = 0;
			acumulador.img = 0;
			for (int i = 0; i < linhas_b; i ++)
			{
				acumulador = soma_complexo(acumulador, multcomp(mtx_a[l][i],mtx_b[i][c]));
			}
			matriz[l][c].real = acumulador.real;
			matriz[l][c].img = acumulador.img;
		}
	}
	return matriz;
}

complexo** produto_por_escalar(complexo **mtx, int linhas, int colunas, int k)
{
	complexo **matriz;

	matriz = allocateComplexMatrix(linhas, colunas);

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			matriz[l][c].real = k*mtx[l][c].real;
			matriz[l][c].img = k*mtx[l][c].img;
		}
	}
	return matriz;
}

void teste_produto_por_escalar(void)
{
	complexo **mtx_a, **mtx_b, **mtx_ka,**mtx_kb;

	int linhas = 3, colunas =3, k = 5;
	//Alocação de memória.
	mtx_a = allocateComplexMatrix(linhas, colunas);
	mtx_b = allocateComplexMatrix(linhas, colunas);

	//Preenchimento da(s) matriz(es).
	printf("\n\n=== Preenchendo as Matrizes ===\n\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			mtx_a[l][c].real = 1 + l + c;
			mtx_a[l][c].img = l*c - 2;
		}
	}

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			mtx_b[l][c].real = 1 + l + c;
			mtx_b[l][c].img = l*c - 2;
		}
	}

	//Impressão da Matriz A.
	printf("\n=== Matriz A ===\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_a[l][c]);
		}
		printf("\n");
	}
	//Chamada da função produto_por_escalar.
	mtx_ka = produto_por_escalar(mtx_a, linhas, colunas, k); 
	//Impressão do resultado.
	printf("\n\n=== Matriz kA ===\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_ka[l][c]);
		}
		printf("\n");
	}
	//Operação para Matriz B.
	printf("\n\n=== Matriz B ===\n");
	//Impressão da Matriz B.
	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_b[l][c]);
		}
		printf("\n");
	}
	//Chamada da função produto_por_escalar.
	mtx_kb = produto_por_escalar(mtx_b, linhas, colunas, k);
	//Impressão do resultado.
	printf("\n\n=== Matriz kB ===\n");
	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_kb[l][c]);
		}
		printf("\n");
	}
}

void teste_produto_matricial(void)
{
	complexo **mtx_a, **mtx_b, **mtx_produto_axb, **mtx_c, **mtx_d, **mtx_produto_cxd, **mtx_e, **mtx_f, **mtx_produto_exf;
	
	int nlinhas_1 = 3, ncolunas_1 = 3, nlinhas_2 = 3, ncolunas_2 = 3;
	
	//Alocação de memória.
	mtx_a = allocateComplexMatrix(nlinhas_1, ncolunas_1);
	mtx_c = allocateComplexMatrix(nlinhas_1, ncolunas_1);
	mtx_e = allocateComplexMatrix(nlinhas_1, ncolunas_1);
	mtx_b = allocateComplexMatrix(nlinhas_2, ncolunas_2);
	mtx_d = allocateComplexMatrix(nlinhas_2, ncolunas_2);
	mtx_f = allocateComplexMatrix(nlinhas_2, ncolunas_2);

	//Preenchimento das matrizes operandas.
	//Matriz A.
	for (int l = 0; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
 			mtx_a[l][c].real = 1 + l;
			mtx_a[l][c].img = 1 + c;
		}
	}
	//Matriz B.
	for (int l = 0; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			mtx_b[l][c].real = 0;
			mtx_b[l][c].img = 1 + c;
		}
	}
	//Matriz C.
	for (int l = 0; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
 			mtx_c[l][c].real = 1 + 2*l;
			mtx_c[l][c].img = 1 - 2*c;
		}
	}
	//Matriz D.
	for (int l = 0; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			mtx_d[l][c].real = l - c;
			mtx_d[l][c].img = -1 - c;
		}
	}
	//Matriz E.
	for (int l = 0; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
 			mtx_e[l][c].real = 2 + l;
			mtx_e[l][c].img = c - 2;
		}
	}
	//Matriz F.
	for (int l = 0; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			mtx_f[l][c].real = 2 + c - l;
			mtx_f[l][c].img = c*l;
		}
	}
	//Primeira Operação.
	printf("\n\n=== Primeira interação: A x B ===\n");
	//Impressão dos Operandos:
	printf("\n\n=== Operando A ===\n");
	//Impressão da matriz A.
	for (int l = 0 ; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
			printComplex(mtx_a[l][c]);
		}
        printf("\n");
	}
	
	printf("\n\n=== Operando B ===\n");
	//Impressão da matriz B.
	for (int l = 0 ; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			printComplex(mtx_b[l][c]);
		}
        printf("\n");
	}
	//Chamada da função produto_matricial.
	mtx_produto_axb = produto_matricial(mtx_a, mtx_b, ncolunas_1, nlinhas_2);
	//Impressão do resultado.
	printf("\n\n=== Resultado A x B ===\n");

	for (int l = 0 ; l < ncolunas_1; l++)
	{
		for (int c = 0; c < nlinhas_2; c++)
		{
			printComplex(mtx_produto_axb[l][c]);
		}
        printf("\n");
	}

	//Segunda Operação.
	printf("\n\n=== Segunda interação: C x D ===\n");
	//Impressão dos Operandos:
	printf("\n\n=== Operando C ===\n");
	//Impressão da matriz C.
	for (int l = 0 ; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
			printComplex(mtx_c[l][c]);
		}
        printf("\n");
	}
	
	printf("\n\n=== Operando D ===\n");
	//Impressão da matriz D.
	for (int l = 0 ; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			printComplex(mtx_d[l][c]);
		}
        printf("\n");
	}
	//Chamada da função produto_matricial
	mtx_produto_cxd = produto_matricial(mtx_c, mtx_d, ncolunas_1, nlinhas_2);
	//Impressão do resultado
	printf("\n\n=== Resultado C x D ===\n");

	for (int l = 0 ; l < ncolunas_1; l++)
	{
		for (int c = 0; c < nlinhas_2; c++)
		{
			printComplex(mtx_produto_cxd[l][c]);
		}
        printf("\n");
	}

	//Terceira Operação.
	printf("\n\n=== Terceira interação: E x F ===\n");
	//Impressão dos Operandos:
	printf("\n\n=== Operando E ===\n");
	//Impressão da matriz E.
	for (int l = 0 ; l < nlinhas_1; l++)
	{
		for (int c = 0; c < ncolunas_1; c++)
		{
			printComplex(mtx_e[l][c]);
		}
        printf("\n");
	}
	
	printf("\n\n=== Operando F ===\n");
	//Impressão da matriz F.
	for (int l = 0 ; l < nlinhas_2; l++)
	{
		for (int c = 0; c < ncolunas_2; c++)
		{
			printComplex(mtx_f[l][c]);
		}
        printf("\n");
	}
	//Chamada da função produto_matricial
	mtx_produto_exf = produto_matricial(mtx_e, mtx_f, ncolunas_1, nlinhas_2);
	//Impressão do resultado
	printf("\n\n=== Resultado E x F ===\n");

	for (int l = 0 ; l < ncolunas_1; l++)
	{
		for (int c = 0; c < nlinhas_2; c++)
		{
			printComplex(mtx_produto_exf[l][c]);
		}
        printf("\n");
	}
}

//Função: Multiplicação de dois complexos.
complexo multcomp(complexo c, complexo c1)
{
	complexo multiplicado;
	multiplicado.real = (c.real*c1.real)-(c.img*c1.img);
	multiplicado.img = (c.real*c1.img)+(c.img*c1.real);
	return multiplicado;
}

/*Teste da função Transposta*/
void teste_transposta(void)
{
	complexo** c1,**c2,**c3,**c4;; //matriz complexa a ser transposta
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=3;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);
	printf("\n===============================Teste da operação Transposta======================\n");
	
        for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = (3*l)-c;
				c1[l][c].img = c+l;
			}
    }
        printf("\nOperando A:\n");
        for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(c1[l][c]);
			}
        printf("\n");
    }
	int nlinhas_trans = ncolunas;
	int ncolunas_trans = nlinhas;
	
	printf("\nResultado R:\n");
    c2 = transposta(c1,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
		{
			for (int c = 0; c < ncolunas_trans; c++)
			{
				printComplex(c2[l][c]);
			}
        printf("\n");
		}
    //Alocação de memoria para a matriz:
    c3 = allocateComplexMatrix(nlinhas,ncolunas);
	
        for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c3[l][c].real = (3*l)+c;
				c3[l][c].img = -c+l;
			}
    }
        printf("\nOperando B:\n");
        for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(c3[l][c]);
			}
        printf("\n");
    }
	
	printf("\nResultado R:\n");
    c4 = transposta(c3,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
		{
			for (int c = 0; c < ncolunas_trans; c++)
			{
				printComplex(c4[l][c]);
			}
        printf("\n");
		}
}

/*Teste da função Soma*/
void teste_soma(void)
{	

	complexo **c1,**c2,**somado1,**c3,**c4,**somado2;
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=3;
    //Alocação de memoria para a matriz:
    c3 = allocateComplexMatrix(nlinhas,ncolunas);
	c4 = allocateComplexMatrix(nlinhas,ncolunas);
	 for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c3[l][c].real = l+1;
				c3[l][c].img = (2*l)-c;
				c4[l][c].real = (5*l)+c;
				c4[l][c].img = l-c;
			}
    }
	printf("\n\n===============================Teste da operação Soma===========================\n");
	printf("\nOperando A:\n");
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c3[l][c]);
				}
			printf("\n");
		}
	printf("\nOperando B:\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c4[l][c]);
				}
			printf("\n");
		}
	printf("\nResultado:\n");
	somado1 = soma(c3,c4,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(somado1[l][c]);
			}
        printf("\n");
	}
	c1 = allocateComplexMatrix(nlinhas,ncolunas);
	c2 = allocateComplexMatrix(nlinhas,ncolunas);
	 for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = l-2;
				c1[l][c].img = (2*l)+c;
				c2[l][c].real = (5*l)-c;
				c2[l][c].img = -l-c;
			}
    }
	printf("\nOperando C:\n");
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c1[l][c]);
				}
			printf("\n");
		}
	printf("\nOperando D:\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c2[l][c]);
				}
			printf("\n");
		}
	printf("\nResultado:\n");
	somado2 = soma(c3,c4,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(somado2[l][c]);
			}
        printf("\n");
	}	
}

void teste_subtracao(void)
{
	complexo **c1,**c2,**sub1,**c3,**c4,**sub2;
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=3;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);
	c2 = allocateComplexMatrix(nlinhas,ncolunas);
	 for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = l+1;
				c1[l][c].img = (2*l)-c;
				c2[l][c].real = (5*l)+c;
				c2[l][c].img = l-c;
			}
    }
	printf("\n\n===============================Teste da operação Subtracao===========================\n");
	printf("\nOperando A:\n");
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c1[l][c]);
				}
			printf("\n");
		}
	printf("\nOperando B:\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c2[l][c]);
				}
			printf("\n");
		}
	printf("\nResultado:\n");
	sub1 = subtracao(c1,c2,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(sub1[l][c]);
			}
        printf("\n");
	}
	c3 = allocateComplexMatrix(nlinhas,ncolunas);
	c4 = allocateComplexMatrix(nlinhas,ncolunas);
	 for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c3[l][c].real = l-2;
				c3[l][c].img = (2*l)+c;
				c4[l][c].real = (5*l)-c;
				c4[l][c].img = -l-c;
			}
    }
	printf("\nOperando C:\n");
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c3[l][c]);
				}
			printf("\n");
		}
	printf("\nOperando D:\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c4[l][c]);
				}
			printf("\n");
		}
	printf("\nResultado:\n");
	sub2 = subtracao(c3,c4,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(sub2[l][c]);
			}
        printf("\n");
	}	
}
	
void teste_todos(void)
{	
	printf("\n===============================Teste da operação Transposta======================\n");
	complexo** c1,**c2; 
	int nlinhas,ncolunas;
    nlinhas=3;
    ncolunas=3;
    //Alocação de memoria para a matriz:
    c1 = allocateComplexMatrix(nlinhas,ncolunas);
	
        for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c1[l][c].real = (2*l)-c;
				c1[l][c].img = c-1+l;
			}
    }
        printf("\nOperando A:\n");
        for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(c1[l][c]);
			}
        printf("\n");
    }
	int nlinhas_trans = ncolunas;
	int ncolunas_trans = nlinhas;
	
	printf("\nResultado R:\n");
    c2 = transposta(c1,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
		{
			for (int c = 0; c < ncolunas_trans; c++)
			{
				printComplex(c2[l][c]);
			}
			printf("\n");
		}
		
	printf("\n\n===============================Teste da operação Soma===========================\n");
	
	complexo **c3,**c4,**somado1;
    //Alocação de memoria para a matriz:
    c3 = allocateComplexMatrix(nlinhas,ncolunas);
	c4 = allocateComplexMatrix(nlinhas,ncolunas);
	for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c3[l][c].real = l+1;
				c3[l][c].img = (2*l)-c;
				c4[l][c].real = (5*l)+c;
				c4[l][c].img = l-c;
			}
		}
	printf("\nOperando A:\n");
	for (int l =0 ; l < nlinhas; l++)
	{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(c3[l][c]);
			}
		printf("\n");
	}
	printf("\nOperando B:\n");
	for (int l =0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(c4[l][c]);
		}
		printf("\n");
	}
	printf("\nResultado:\n");
	somado1 = soma(c3,c4,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(somado1[l][c]);
		}
		printf("\n");
	}
	
	printf("\n\n===============================Teste da operação Subtracao===========================\n");
	complexo **c5,**c6,**sub1;
    //Alocação de memoria para a matriz:
    c5 = allocateComplexMatrix(nlinhas,ncolunas);
	c6 = allocateComplexMatrix(nlinhas,ncolunas);
	for (int l = 0; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				c5[l][c].real = l-1;
				c5[l][c].img = (3*l)-2*c;
				c6[l][c].real = (4*l)-c;
				c6[l][c].img = -l-c;
			}
    }
	
	printf("\nOperando A:\n");
		for (int l =0 ; l < nlinhas; l++)
		{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c5[l][c]);
				}
			printf("\n");
		}
	printf("\nOperando B:\n");
		for (int l =0 ; l < nlinhas; l++)
			{
				for (int c = 0; c < ncolunas; c++)
				{
					printComplex(c6[l][c]);
				}
			printf("\n");
		}
	printf("\nResultado:\n");
	sub1 = subtracao(c5,c6,nlinhas,ncolunas);
	for (int l =0 ; l < nlinhas; l++)
		{
			for (int c = 0; c < ncolunas; c++)
			{
				printComplex(sub1[l][c]);
			}
        printf("\n");
	}

	printf("\n\n===============================Teste da operação Produto Matricial===========================\n\n");

	complexo **mtx_7, **mtx_8, **mtx_produto;
	
	int nlinhas_7 = 3, ncolunas_7 = 3, nlinhas_8 = 3, ncolunas_8 = 3;
	
	//Alocação de memória.
	mtx_7 = allocateComplexMatrix(nlinhas_7, ncolunas_7);
	mtx_8 = allocateComplexMatrix(nlinhas_8, ncolunas_8);

	//Preenchimento das matrizes operandas.
	for (int l = 0; l < nlinhas_7; l++)
	{
		for (int c = 0; c < ncolunas_7; c++)
		{
 			mtx_7[l][c].real = 1 + l;
			mtx_7[l][c].img = 1 + c;
		}
	}

	for (int l = 0; l < nlinhas_8; l++)
	{
		for (int c = 0; c < ncolunas_8; c++)
		{
			mtx_8[l][c].real = 0;
			mtx_8[l][c].img = 1 + c;
		}
	}
	//Impressão dos Operandos:
	printf("\n=== Operando A ===\n");
	//Impressão da matriz A.
	for (int l = 0 ; l < nlinhas_7; l++)
	{
		for (int c = 0; c < ncolunas_7; c++)
		{
			printComplex(mtx_7[l][c]);
		}
        printf("\n");
	}
	
	printf("\n=== Operando B ===\n");
	//Impressão da matriz B.
	for (int l = 0 ; l < nlinhas_8; l++)
	{
		for (int c = 0; c < ncolunas_8; c++)
		{
			printComplex(mtx_8[l][c]);
		}
        printf("\n");
	}
	//Chamada da função produto_matricial
	mtx_produto = produto_matricial(mtx_7, mtx_8, ncolunas_7, nlinhas_8);
	//Impressão do resultado
	printf("\n=== Resultado C = A x B ===\n");

	for (int l = 0 ; l < nlinhas_7; l++)
	{
		for (int c = 0; c < ncolunas_8; c++)
		{
			printComplex(mtx_produto[l][c]);
		}
        printf("\n");
	}

	printf("\n\n===== Teste da função Conjugada =====\n\n");
//Kauan (06.05.23)
	complexo **c10, **conj_c10;

	//Alocação de memória. 
	c10 = allocateComplexMatrix(nlinhas, ncolunas);

	//Preenchimento da(s) matriz(es).
	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			c10[l][c].real = l + c;
			c10[l][c].img = 1 + l + c;
		}
	}

	//Chamada da função conjugada.
	conj_c10 = conjugada(c10, nlinhas, ncolunas);

	printf("\n=== Operando A ===\n");
	//Impressão da Matriz A.
	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(c10[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Resultado ===\n");
	//Impressão da(s) matriz(es) conjugada(s)
	printf("\n=== Conjugada de A ===\n");

	for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(conj_c10[l][c]);
		}
		printf("\n");
	}
	//Finalização do teste.
	printf("\n=== Fim do teste da função conjugada() ===\n");

//Kauan (06.05.23)
	printf("\n===== Teste da função Hermetiana =====\n");

	complexo **mtx_a, **mtx_h;

    mtx_a = allocateComplexMatrix(nlinhas, ncolunas);

    for (int l = 0; l < ncolunas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
            mtx_a[l][c].real = l + c;
            mtx_a[l][c].img = l - 2*c;
        }
    }

    printf("\n=== Operando A ===\n");

    for (int l = 0 ; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_a[l][c]);
		}
        printf("\n");
	}

    mtx_h = hermetiana(mtx_a, nlinhas, ncolunas);

	printf("\n=== Matriz Hermetiana de A ===\n");

    for (int l = 0 ; l < nlinhas_trans; l++)
	{
		for (int c = 0; c < ncolunas_trans; c++)
		{
			printComplex(mtx_h[l][c]);
		}
        printf("\n");
	}
	//Finalização do teste Hermetiano.
	printf("\n===== Fim do teste da função Hermetiana =====\n");

	complexo **mtx_12, **mtx_k12;

	int linhas = 3, colunas =3, k = 5;
	//Alocação de memória.
	mtx_12 = allocateComplexMatrix(linhas, colunas);

	//Preenchimento da(s) matriz(es).
	printf("\n\n=== Preenchendo a(s) Matriz(es) ===\n\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			mtx_12[l][c].real = 1 + l + c;
			mtx_12[l][c].img = l*c - 2;
		}
	}
	//Impressão da Matriz A.
	printf("\n=== Matriz A ===\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_12[l][c]);
		}
		printf("\n");
	}
	//Chamada da função produto_por_escalar.
	mtx_k12 = produto_por_escalar(mtx_12, linhas, colunas, k); 
	//Impressão do resultado.
	printf("\n\n=== Matriz kA ===\n");

	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
		{
			printComplex(mtx_k12[l][c]);
		}
		printf("\n");
	}
	printf("\n=== Fim do teste produto_por_escalar ===\n");
}
