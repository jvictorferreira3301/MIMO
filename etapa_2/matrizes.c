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
	
/*Printa o complexo C*/
void printComplex(complexo z)
{
    printf("%+.2f %+.2fj ", z.real, z.img);
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
	
}
	