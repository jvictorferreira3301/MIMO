#include <stdio.h>
#include <stdlib.h>
#include "meucomplexo.h"

int main (void)
{
    complexo c1, c2, c3;
    
    c1.real = 3;
    c1.img = 4;

    c2.real = 4;
    c2.img = -6;

    c3 = somaComplexo (c1, c2);

    printComplexo(c3);

    return 0;
}