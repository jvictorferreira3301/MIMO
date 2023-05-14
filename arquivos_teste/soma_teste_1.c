#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float real, img;
}Complexo;
//imprimir um numero complexo z;
void printComplex(Complexo z)
{
    printf("%+.2f %+.2fj", z.real, z.img);
}

Complexo** allocateComplexMatrix (int linhas, int colunas)
{
    Complexo** matrix;

    matrix = (Complexo **) malloc(linhas*sizeof(Complexo*));

    if (matrix == NULL)
    {
        printf("Memory alocation failed.");
        exit(1);
    }
    //alocação de memória para cada linha da matriz
    for (int i = 0; i < colunas; i++)
    {
        matrix[i] = (Complexo *) malloc(colunas*sizeof(Complexo));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    return matrix;
}

Complexo** addComplexMatrix (Complexo** matrix_a, Complexo** matrix_b, int linhas, int colunas)
{
    Complexo** matrix;

    matrix = allocateComplexMatrix(linhas, colunas);

    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            matrix[l][c].real = matrix_a[l][c].real + matrix_b[l][c].real;
            matrix[l][c].img = matrix_a[l][c].img + matrix_b[l][c].img;
        }
    }

    return matrix;
}

void main()
{
    Complexo** mtx_a, **mtx_b, **mtx_c;

    int nlinhas, ncolunas;

    printf("Digite a dimensao das matrizes (Linhas e depois Colunas): \n");
    scanf("%d", &nlinhas);
    scanf("%d", &ncolunas);
    printf("\nSuas matrizes foram definidas em %dx%d\n", nlinhas, ncolunas);

    if(nlinhas > 10 || ncolunas > 10)
    {
        printf("\nA dimensão das matrizes excederam o limite.\n");
        exit(1);
    }

//alocação de memória para matriz A e B

    mtx_a = allocateComplexMatrix(nlinhas, ncolunas);
    mtx_b = allocateComplexMatrix(nlinhas, ncolunas);

//Leitura da matriz A

    printf("\nPreencha a matriz A linha por linha: \n");

    for(int l = 0; l < ncolunas; l++)
    {
        for(int c = 0; c < ncolunas; c++)
        {
            printf("\nmtx_a[%d][%d].real: ", l, c);
            scanf("%f", &mtx_a[l][c].real);
            fflush(stdin);
            printf("mtx_a[%d][%d].img: ", l, c);
            scanf("%f", &mtx_a[l][c].img);
            fflush(stdin);
        }

    }

//tentativa de leitura da matriz B

    printf("\nPreencha a matriz B linha por linha: \n");

    for(int l = 0; l < ncolunas; l++)
    {
        for(int c = 0; c < ncolunas; c++)
        {
            printf("\nmtx_b[%d][%d].real: ", l, c);
            scanf("%f", &mtx_b[l][c].real);
            fflush(stdin);
            printf("mtx_b[%d][%d].img: ", l, c);
            scanf("%f", &mtx_b[l][c].img);
            fflush(stdin);
        }
    }

//tentativa de puxar uma função de soma

    mtx_c = addComplexMatrix(mtx_a, mtx_b, nlinhas, ncolunas);

//imprimindo

    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
         {
            printf("\nmtx_c[%d][%d]: ",l,c);
            printComplex(mtx_c[l][c]);
        }
    }

//tentativa de imprimir a matriz formatada

/*   printf("\t\t");
    for (int c = 0; c < ncolunas; c++)
        {
            printf("%d\t\t", c);
        }
    printf("\n\n");

      for (int l = 0; l < nlinhas; l++)
    {
        printf("%d\t", l);
        for (int c = 0; c < ncolunas; c++)
        {
            printComplex(mtx_c[l][c]);
            printf("\t");
        }
        printf("\n");
    }
*/
}   
    