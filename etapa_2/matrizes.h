#ifndef MATRIZES_H
#define MATRIZES_H

typedef struct {
    double real;
    double imag;
} Complexo;

typedef struct {
    int linhas;
    int colunas;
    Complexo **elementos;
} MatrizComplexa;

MatrizComplexa cMatrizComplexa(int linhas, int colunas); //aloca��o din�mica
void libMatrizComplexa(MatrizComplexa *matriz); // 
MatrizComplexa somaMatrizesComplexas(MatrizComplexa matriz1, MatrizComplexa matriz2); // recebe duas matrizes como par�metro e retorna a soma delas

#endif
