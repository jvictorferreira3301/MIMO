#include <stdio.h>
#include <stdlib.h>
//estrutura
typedef struct{
    float real, img;
}complexo;

//função print
void printComplex(complexo z)
{
    printf("%+.2f %+.2fj", z.real, z.img);
}

//função de alocação 
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
    for (int i = 0; i < colunas; i++)
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
//função conjugado de uma matriz declarada em main
complexo** conjugado(complexo **mtx, int linhas, int colunas)
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

int main()
{

    complexo **mtx_a, **mtx_c;

    int nlinhas, ncolunas;
    //inserção da dimensão da matriz
    printf("Digite a dimensao das matrizes (Linhas e depois Colunas): \n");
    scanf("%d", &nlinhas);
    scanf("%d", &ncolunas);
    printf("\nSuas matrizes foram definidas em %dx%d\n", nlinhas, ncolunas);
    //verificação da validadade da dimensão
    if(nlinhas > 10 || ncolunas > 10)
    {
        printf("\nA dimensão das matrizes excederam o limite.\n");
        exit(1);
    }

    //alocação

    mtx_a = allocateComplexMatrix(nlinhas, ncolunas);

    //leitura da matriz A  

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

    //chamada da função conjugado

    mtx_c = conjugado(mtx_a, nlinhas, ncolunas);
    //impressão da matriz
    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
         {
            printf("\nmtx_c[%d][%d]: ",l,c);
            printComplex(mtx_c[l][c]);
        }
    }

    return 0;
}



