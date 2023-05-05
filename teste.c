#include <stdio.h>

typedef struct{
int linha;
int coluna;
}matriz_complexa;

typedef struct{
float real;
float img;
}complexo;

int main()
{
    int i,j;
    complexo matriz[2][2],matriz2[2][2],soma[2][2];
    complexo c1,c2,c3,c4;
    c1.real=1;
    c1.img=-2;
    c2.real=2;
    c2.img=-8;
    c3.real=4;
    c3.img=2;
    c4.real=23;
    c4.img=2;
    matriz[0][0]=c1;
    matriz[0][1]=c2;
    matriz[1][0]= c3;
    matriz[1][1]=c4;
    matriz2[0][0]=c3;
    matriz2[0][1]=c1;
    matriz2[1][0]= c4;
    matriz2[1][1]=c2;
    printf("================Teste1=================\n");
    printf("Operando A: \n");
    for(i=0;i<2;i++){
        for(j=0;j<2;j++)
            printf("(%f + %fi) ",matriz[i][j].real,matriz[i][j].img);
        printf("\n");
    }
    printf("\n\nOperando B: \n");
    for(i=0;i<2;i++){
        for(j=0;j<2;j++)
            printf("(%f + %fi) ",matriz2[i][j].real,matriz2[i][j].img);
        printf("\n");
    }
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            soma[i][j].real = matriz[i][j].real + matriz2[i][j].real;
            soma[i][j].img = matriz[i][j].img + matriz2[i][j].img;
        }
    }
    printf("\n\nSoma:\n");
    for(i=0;i<2;i++){
        for(j=0;j<2;j++)
            printf("(%f + %fi) ",soma[i][j].real,soma[i][j].img);
        printf("\n");
    }
return 0;
}
