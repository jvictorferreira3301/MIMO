//=========Matriz.h==================
#ifndef _H_MYCOMPLEX
#define _H_MYCOMPLEX

/*Estrutura das variáveis complexas*/
typedef  struct complexo
	{
		float real;
		float img;
	}complexo;
	
/* a função que faz a transposta da matriz*/
complexo** transposta(complexo** c,int linhas, int colunas);

/* Alocação de memoria para uma matriz complexa*/
complexo** allocateComplexMatrix(int linhas, int colunas);

/*Printa o complexo c*/
void printComplex(complexo c);

/*Multiplica dois complexos*/
complexo multcomp(complexo c,complexo c1);

/*Soma duas matrizes complexas*/
complexo** soma(complexo** c, complexo** c1, int linhas, int colunas);

/*Subtrai duas matrizes complexas*/
complexo** subtracao(complexo** c, complexo** c2, int linhas, int colunas);

/*Multiplica duas matrizes*/
complexo** produto_matricial(complexo **mtx_a, complexo **mtx_b, int linhas, int colunas);

complexo** conjugada(complexo **mtx, int linhas, int colunas);

complexo** hermetiana(complexo **mtx, int linhas, int colunas);

void teste_conjugada(void);
void teste_transposta(void);
void teste_hermetiana(void);

void teste_soma(void);
void teste_subtracao(void);

void teste_todos(void);
#endif