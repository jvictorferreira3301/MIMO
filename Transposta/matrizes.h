//=========Matriz.h==================
#ifndef _H_MYCOMPLEX
#define _H_MYCOMPLEX

typedef  struct complexo
	{
		float real;
		float img;
	}complexo;
	
/* a função que faz a transposta da matriz*/
complexo** transposta(complexo** c,int linhas, int colunas);

complexo** allocateComplexMatrix(int linhas, int colunas);

void printcomplexo(complexo c);

#endif