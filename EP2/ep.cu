/** 
* André Luiz Abdalla Silveira 8030353
* Mauricio Luiz Cardoso 0000000
* 
* Esse programa escrito em CUDA visa criar um algoritmo que gera uma redução
*   de matrizes. Cada matriz é representada por um vetor e todos estão 
*   reunidos num vetor de vetores. A ideia é fazer uma função que faz uma 
*   comparação entre vetores fazendo o mínimo de operações
*
*   Observação pro Mauricio (delete depois de ler): depois de passar um tempão
*   pensando numa solução mais elegante, eu percebi que o número de comparações
*   é o mesmo se compararmos com uma implemetação onde se contrapõem dois vetores
*   iniciais, e o resultante da comparação com o próximo, e por aí vai.
*   O que falta? 1- leitura de arquivos 2- fazer a parte de CUDA 3- corrigir eventuais
*                                   bugs
*/

#include <stdio.h>
#include <stdlib.h>
#define E 9 // qtde de elementos de cada matriz
#define linhaElementos 3 // quantidade de elementos da linha 
int numMatrizes;

/* pedaço de código copaido da apresentação, deve ser alterado sob demanda */
__global__ void os_menores(int *a, int *b, int *c) {
    c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

/* Imprime todas as matrizes de dimensão ExE contidas en nat*/
void leitura (int *mat) {
    int i, k;
    for (i = 0; i < numMatrizes * linhaElementos; i++) {
        for (k = 0; k < linhaElementos; k++) 
            printf("%d\t", *(mat++));
        printf("\n");
        if((i+1) % linhaElementos == 0)
            printf("********************\n");
    }
}

int * compara (int *a, int *b) { /* Muitas coisas copiadas dos slides 36 e 37 */
    int *resp, tam = E * sizeof(int);
    int *d_a, *d_b, *d_resp;
    int N = 32;
    
    // Alloc space for device copies of a, b, c
    cudaMalloc((void **) &d_a, tam);
    cudaMalloc((void **) &d_b, tam);
    cudaMalloc((void **) &d_resp, tam);

    // Copy inputs to device
    cudaMemcpy(d_a, a, tam, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, tam, cudaMemcpyHostToDevice);

    // Launch add() kernel on GPU with N threads -- mudar o valor de N
    os_menores<<<1,N>>>(d_a, d_b, d_resp);

    // Copy result back to host
    cudaMemcpy(resp, d_resp, tam, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_resp);
    return resp;
}

// int * get_min (int **mat, int ini, int fim) {
//  int *parteA, *parteB;
//  if (ini - fim > 1){ /* mais que 2 elementos*/
//      meio = (ini + fim)/2;
//      parteA = get_min(mat, ini, meio);
//      parteB = get_min(mat, meio + 1, fim);
//      return compara(parteA, parteB);
//  }else if (ini - fim == 1){ /* 2 elementos */
//      return compara(mat[ini], mat[fim]);
//  }
//  else {
//      return mat[ini];
//  }
// }

// void apaga (int **mat){
//  int i;
//  int linhas = (sizeof(mat)/sizeof(int *));
//  for (i = 0; i < linhas; ++i) {
//      free(mat[i]);
//  }
//  free(mat);
// }


/* Le o arquivo arq que contem matrizes no formato declarado
no enunciado e retorna um vetor com todas matrizes lidas*/
int* alocaMatrizesArquivo(FILE *arq){
    char asteriscos[10];
    int *matrizes, *matrizesAux;
    fscanf(arq, "%d", &numMatrizes);
    matrizes =  (int *) malloc(E * numMatrizes * sizeof(int));
    
    matrizesAux = matrizes;
    for(int i = 0; i < numMatrizes; i++) {
        fscanf(arq, "%s", asteriscos); //pula a linha de asteriscos
        for(int j = 0; j < E; j++)
            fscanf(arq, "%d", matrizesAux++);
    }
    leitura(matrizes);
    return matrizes;
}


int main (int argc, char* argv[]) {
    if(argc != 2) {
        printf("Argumento do programa: nome do arquivo\n");
    }
    else {  
        FILE *entrada;
        entrada =  fopen(argv[1], "r");
        if (entrada == NULL) {
            printf("Deu ruim pra abrir o arquivo\n");
            return EXIT_FAILURE;
        }
        int *matrizes = alocaMatrizesArquivo(entrada);

        fclose(entrada);
        // leitura(get_min(mat, 0, qtde));
        free(matrizes);
    }
}

