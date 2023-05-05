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

/* Alocação de memoria para uma matriz complexa*/
complexo** allocateComplexMatrix(int linhas, int colunas);

/*Printa o complexo C*/
void printComplex(complexo c);

/*Multiplica dois complexos*/
complexo multcomp(complexo c,complexo c1);

/*Soma duas matrizes complexas*/
complexo** somacomp(complexo** c, complexo** c1, int linhas, int colunas);
#endif