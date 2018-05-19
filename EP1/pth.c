#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int ** le_matriz (int ** matriz, int linhas, int colunas, FILE * arq){
    int i, l, c, valor;
    matriz = malloc(linhas * sizeof(int *));
    for (i = 0; i < linhas; ++i) {
        matriz[i] = calloc(colunas, sizeof(int));
    }
    while (fscanf(a, "%d", l) != EOF) {
        fscanf(a, "%d", c);
        fscanf(a, "%f", valor);
        matriz[l][c] = valor;
    }
}

int ** imprime_matriz (int ** matriz, int linhas, int colunas, FILE * arq){
    int l, c, valor;
    fprintf(arq, "%d %d\n", linhas, colunas);
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            if (valor > 0.0) fprinf("%d %d %f\n", linhas, colunas, valor);
        }
    }
}

void apaga (int ** mat, int linhas){
    int i;
    for (i = 0; i < linhas; ++i) {
        free(mat[i]);
    }
    free(mat);
}


int main (int argc, char ** argv){
    FILE *a, *b, *c;
    int la, ca, lb, cb;
    int **mat_a, **mat_b, **mat_c;

    a = fopen(argv[1], "r");
    b = fopen(argv[1], "r");
    c = fopen(argv[1], "w");
    if (a == NULL || b == NULL || c == NULL){
        printf("Deu ruim com algum arquivo");
        return 1;
    }

    fscanf(a, "%d", la);
    fscanf(a, "%d", ca);
    fscanf(b, "%d", lb);
    fscanf(b, "%d", cb);
    if (ca != lb) {
        printf("Não vai dar pra multiplicar as matrizes");
        return 1;
    }

    le_matriz(mat_a, la, ca, a);
    le_matriz(mat_b, lb, cb, b);

    /* multiplicação*/

    imprime_matriz(mat_c, la, cb);
    apaga(mat_a,la);
    apaga(mat_b,lb);
    apaga(mat_c,la);
    return 0;
}