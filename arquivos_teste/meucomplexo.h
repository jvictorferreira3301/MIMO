#ifndef _H_MEUCOMPLEXO
#define _H_MEUCOMPLEXO

typedef struct{
    float real, img;
}complexo;

complexo somaComplexo (complexo a, complexo b);

void printComplexo (complexo z);

#endif