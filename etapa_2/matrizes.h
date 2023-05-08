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
