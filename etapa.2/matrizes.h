/* Definindo a estrutura para armazenar números complexos */
typedef struct {
    float re; /* Parte real*/
    float img; /* Parte Imaginária*/
} complexo;

/* Assinatura da função de subtração*/
void subtracao(int a, int b, complexo m1[a][b], complexo m2[a][b], complexo resultado[a][b]);
void teste_subtracao(int m, int n, complexo z1[m][n], complexo z2[m][n], complexo result[m][n]);