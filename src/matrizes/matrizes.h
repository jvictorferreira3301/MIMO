/// @file Main.H
#ifndef _H_MYCOMPLEX
#define _H_MYCOMPLEX

#include <stdlib.h>

/** A definição do código apresenta uma estrutura chamada `complexo` que é utilizada para representar números complexos. A estrutura possui dois campos: `real` e `img`, ambos do tipo `float`. 
*O campo `real` é responsável por armazenar a parte real do número complexo, enquanto o campo `img` é utilizado para armazenar a parte imaginária. Essa estrutura é útil para armazenar e manipular números complexos em programas escritos em linguagem C.
 Essa definição de estrutura pode ser incluída em programas C que envolvem cálculos com números complexos, permitindo uma organização clara e acessível dos dados relacionados a números complexos.
 */
typedef struct complexo {
    float real; ///< Parte real
    float img; ///< Parte imaginária
} complexo;

complexo soma_complexo(complexo c1, complexo c2);

/* Alocação de memoria para uma matriz complexa*/
complexo** allocateComplexMatrix(int linhas, int colunas);

/* Liberação de memória de uma matriz complexa*/
void LiberarMatriz(complexo **mtx, int linhas);

/* a função que faz a transposta da matriz*/
complexo** transposta(complexo **mtx, int linhas, int colunas);

/* Printa o complexo c */
void printComplex(complexo c);

/* Multiplica dois complexos */
complexo multcomp(complexo c1, complexo c2);

/* Soma duas matrizes complexas */
complexo** soma(complexo **mtx_a, complexo **mtx_b, int linhas, int colunas);

/* Subtrai duas matrizes complexas */
complexo** subtracao(complexo **mtx_a, complexo **mtx_b, int linhas, int colunas);

/* Multiplica duas matrizes */
complexo** produto_matricial(complexo **mtx_a, complexo **mtx_b, int linhas, int colunas);

/* Calcula o produto interno entre dois vetores */
complexo produto_interno(complexo **v1, complexo **v2, int linhas, int colunas);

complexo** conjugada(complexo **mtx, int linhas, int colunas);

complexo** hermetiana(complexo **mtx, int linhas, int colunas);

complexo** produto_por_escalar(complexo **mtx, int linhas, int colunas, int k);

void teste_conjugada(void);
void teste_transposta(void);
void teste_hermetiana(void);
void teste_soma(void);
void teste_subtracao(void);
void teste_todos(void);
void teste_produto_interno(void);
void teste_produto_matricial(void);
#endif
