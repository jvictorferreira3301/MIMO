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

		for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_b[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Operando B ===\n");
	//Impressão da Matriz B.
		for (int l = 0; l < nlinhas; l++)
	{
		for (int c = 0; c < ncolunas; c++)
		{
			printComplex(mtx_c[l][c]);
		}
		printf("\n");
	}

	printf("\n=== Operando C ===\n");
	//Impressão da Matriz C.

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
complexo** produto_matricial(complexo** c1, complexo **c2,int linhas_c1, int colunas_c2)
{
	complexo** matrix;
	
	matrix = allocateComplexMatrix(linhas_c1,colunas_c2);
		for (int l = 0; l < linhas_c1; l++)
		{
			for (int c = 0; c < colunas_c2; c++)
			{
				matrix[l][c] = multcomp(c1[l][c],c2[l][c]);
			}
		}
	return matrix;
}

/*Multiplica dois complexos*/
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

	printf("\n\n===============================Teste da operação Produto Matricial===========================\n");
	complexo **c7,**c8,**produto_matricial;
	int linhas_c7, colunas_c7;
	int linhas_c8, colunas_c8;
    //Alocação de memoria para a matriz:
    c7 = allocateComplexMatrix(nlinhas,ncolunas);
	c8 = allocateComplexMatrix(nlinhas,ncolunas);
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
}
