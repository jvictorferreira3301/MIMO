#include <stdio.h>
#include <stdlib.h>
#include "mycomplex.h"

int main()
{
    Complexo **mtx;

    //int nlinha = dimensionComplexMatrix(nlinha);
    int nlinhas = 2;
    int ncolunas = 4;

    mtx = allocateComplexMatrix(nlinhas, ncolunas);

    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
        {
            mtx[l][c].real = 2*1;
            mtx[l][c].img = 2*c;
        }
    }

    for (int l = 0; l < nlinhas; l++)
    {
        for (int c = 0; c < ncolunas; c++)
         {
            printf("mtx[%d][%d]: ",l,c);
            printComplex(mtx[l][c]);
        }
    }
return 0;
}

