#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void le_matriz (double **matriz, int linhas, int colunas, FILE *arq){
    int l, c;
    double valor;
    matriz = malloc(linhas * sizeof(double *));

    for (l = 0; l < linhas; ++l) {
        matriz[l] = calloc(colunas, sizeof(double));
    }
    while (fscanf(arq, "%d", &l) != EOF) {
        fscanf(arq, "%d", &c);
        fscanf(arq, "%lf", &valor);
        matriz[l][c] = valor;
    }
}

void imprime_matriz_arquivo (double **matriz, int linhas, int colunas, FILE *arq){
    int l, c;
    double valor = 0;
    fprintf(arq, "%d %d\n", linhas, colunas);
    for (l = 0; l < linhas; ++l) {
        for (c = 0; c < colunas; ++c) {
            if (valor != 0.0) fprintf("%d %d %lf\n", linhas, colunas, valor);
        }
    }
}

void apaga (double **mat, int linhas){
    int i;
    for (i = 0; i < linhas; ++i) {
        free(mat[i]);
    }
    free(mat);
}


int main (int argc, char **argv){
    FILE *arqMatA, *arqMatB, *arqMatC;
    int la, ca, lb, cb;
    double **mat_a, **mat_b, **mat_c;

    arqMatA = fopen(argv[1], "r");
    arqMatB = fopen(argv[2], "r");
    arqMatC = fopen(argv[3], "w");
    if (arqMatA == NULL || arqMatB == NULL || arqMatC == NULL){
        printf("Deu ruim com algum arquivo\n");
        return EXIT_FAILURE;
    }

    if(fscanf(arqMatA, "%d", &la))
    fscanf(arqMatA, "%d", &ca);
    fscanf(arqMatB, "%d", &lb);
    fscanf(arqMatB, "%d", &cb);
    if (ca != lb) { 
        printf("Numeros de colunas de A e linhas de B devem ser iguais\n");
        return EXIT_FAILURE;
    }

    le_matriz(mat_a, la, ca, arqMatA);
    le_matriz(mat_b, lb, cb, arqMatB);

    /* multiplicação*/


    /*imprime_matriz(mat_c, *la, *cb);*/
    apaga(mat_a, la);
    apaga(mat_b, lb);
    /*apaga(mat_c, *la);*/
    return EXIT_SUCCESS;
}