#ifndef _H_MYCOMPLEX
#define _H_MYCOMPLEX

typedef struct{
    float real, img;
}Complexo;

Complexo **allocateComplexMatrix (int linhas, int colunas);

void printComplex(Complexo z);

int dimensionComplexMatrix(int n, int m);

#endif
