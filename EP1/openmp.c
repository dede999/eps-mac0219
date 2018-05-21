#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

double** le_matriz (int linhas, int colunas, FILE *arq){
    int l, c;
    double valor;
    double **matriz = malloc(linhas * sizeof(double *));

    for (l = 0; l < linhas; ++l) {
        matriz[l] = calloc(colunas, sizeof(double));
    }

    while (fscanf(arq, "%d", &l) != EOF) {
        fscanf(arq, "%d", &c);
        fscanf(arq, "%lf", &valor);        
        matriz[l-1][c-1] = valor;
    }
    return matriz;
}

void imprime_matriz_arquivo (double **matriz, int linhas, int colunas, FILE *arq){
    int l, c;
    double valor = 0;
    fprintf(arq, "%d %d\n", linhas, colunas);
    for (l = 0; l < linhas; ++l) {
        for (c = 0; c < colunas; ++c) {
            if (matriz[l][c] != 0.0) 
                fprintf(arq, "%d %d %.2lf\n", l + 1, c + 1, matriz[l][c]);
        }
    }
}

double** multiplicaMatrizes(double **mat_a, double **mat_b, int la, int ca, int cb) {
    int c, d, k;
    double sum = 0;
    int numCpu = sysconf(_SC_NPROCESSORS_ONLN);

    double **mat_c = malloc (ca * sizeof(double *));
    for (c = 0; c < la; c++)
        mat_c[c] = malloc (cb * sizeof(double));

    #pragma omp parallel for schedule(static, 2) num_threads(numCpu)
    for (c = 0; c < la; c++) {
      for (d = 0; d < cb; d++) {
        for (k = 0; k < ca; k++) {
          sum = sum + mat_a[c][k]*mat_b[k][d];
        } 
        mat_c[c][d] = sum;
        sum = 0;
      }
    }

    return mat_c;
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

    fscanf(arqMatA, "%d", &la);
    fscanf(arqMatA, "%d", &ca);
    fscanf(arqMatB, "%d", &lb);
    fscanf(arqMatB, "%d", &cb);
    if (ca != lb) { 
        printf("Numeros de colunas de A e linhas de B devem ser iguais\n");
        return EXIT_FAILURE;
    }

    mat_a = le_matriz(la, ca, arqMatA);
    mat_b = le_matriz(lb, cb, arqMatB);

    /* multiplicação*/
    mat_c = multiplicaMatrizes(mat_a, mat_b, la, ca, cb);

    imprime_matriz_arquivo(mat_c, la, cb, arqMatC);

    /*imprime_matriz(mat_c, *la, *cb);*/
    apaga(mat_a, la);
    apaga(mat_b, lb);
    apaga(mat_c, la);
    return EXIT_SUCCESS;
}
