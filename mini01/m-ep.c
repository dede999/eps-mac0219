#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define VECS 500 /* quantidade de vetores */
#define TAM 1000000 /* tamanho do vetor */

int main() {
    /* declaração de variáveis */
    int i, j, k;
    clock_t start_t, end_t;
    double total_h, total_m;
    int ** mat = malloc(VECS * sizeof(int *));

    for (i = 0; i < VECS; ++i) {
        mat[i] = calloc (TAM, sizeof(int));
    }

    /* percorrendo por linha */
    start_t = clock();
    for (j = 0; j < VECS; ++j) {
        for (k = 0; k < TAM; k++) mat[j][k] += 1;
    }
    end_t = clock();
    total_h = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    /* percorrendo por coluna */
    start_t = clock();
    for (j = 0; j < TAM; ++j) {
        for (k = 0; k < VECS; k++) mat[k][j] += 1;
    }
    end_t = clock();
    total_m = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    /* liberando os vetores */
    for (i = 0; i < VECS; ++i) {
        free(mat[i]);
    }
    free(mat);

    printf("Percorrendo por linha =  %f \nPercorrendo por coluna =  %f\n", total_h, total_m);
    return 0;
}