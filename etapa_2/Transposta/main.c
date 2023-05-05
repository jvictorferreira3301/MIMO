#include <stdio.h>
#include <stdlib.h>


typedef struct{
    float real, img;
}complexo;
//imprimir um numero complexo z;
void printComplex(complexo z)
{
    printf("%+.2f %+.2fj ", z.real, z.img);
}

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


int main(void)
{
        complexo** c1,**c2; //matriz complexa a ser transposta
        int nlinhas,ncolunas;
        nlinhas=3;
        ncolunas=2;
        //Alocação de memoria para a matriz:
        c1 = allocateComplexMatrix(nlinhas,ncolunas);

        //Insira os valores de c1:
        for (int j = 0; j < nlinhas; j++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
            c1[j][c].real = (3*j)-c;
                        c1[j][c].img = c+j;
        }
    }
        printf("Matriz A:\n");
        for (int j =0 ; j < nlinhas; j++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
           printComplex(c1[j][c]);
        }
                printf("\n");
    }
    int nlinhas_trans = ncolunas;
    int ncolunas_trans = nlinhas;
        printf("\n Transporta de A:\n");
        c2 = transposta(c1,nlinhas_trans,ncolunas_trans);
        for (int l =0 ; l < nlinhas_trans; l++)
    {
        for (int c = 0; c < ncolunas_trans; c++)
        {
           printComplex(c2[l][c]);
        }
                printf("\n");
    }
        return(0);

}
