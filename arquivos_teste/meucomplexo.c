#include <stdio.h>
#include <stdlib.h>
#include "meucomplexo.h"

complexo somaComplexo (complexo a, complexo b)
{
    complexo z;
    z.real = a.real + b.real;
    z.img = a.img + b.img;
    return z;
}

void printComplexo (complexo z)
{
    printf("%+f%+fj\n", z.real, z.img);
}