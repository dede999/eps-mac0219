/** 
* André Luiz Abdalla Silveira 8030353
* Mauricio Luiz Cardoso 6796479
* 
* Esse programa escrito em CUDA visa criar um algoritmo que gera uma redução
*   de matrizes. Cada matriz é representada por um vetor e todos estão 
*   reunidos num vetor de vetores. A ideia é fazer uma função que faz uma 
*   comparação entre vetores fazendo o mínimo de operações
*/

#include <stdio.h>
#include <stdlib.h>
#define E 9 // qtde de elementos de cada matriz
#define linhaElementos 3 // quantidade de elementos da linha 
int numMatrizes;


__global__ void os_menores(int *d_matrizes, int posLimite, int jump) {
  int indexIni = threadIdx.x + blockIdx.x * blockDim.x;

  for(int i = indexIni; i < posLimite; i += jump)
    if(d_matrizes[indexIni] > d_matrizes[i])
      d_matrizes[indexIni] = d_matrizes[i];

}

/* Imprime todas as matrizes de dimensão ExE contidas em matrizes*/
void leitura (int *matrizes, int numMats) {
  int i, k;
  for (i = 0; i < numMats * linhaElementos; i++) {
    for (k = 0; k < linhaElementos; k++) 
      printf("%d\t", *(matrizes++));
    printf("\n");
    if((i+1) % linhaElementos == 0)
      printf("********************\n");
  }
}


void menorMatriz(int *d_matrizes, int numMats) {
	if(numMats > 1) {
	  int numBlocks = 0;
	  int numMatResto;
    int jump = 0;
	  int numThreads = 0;
    int posLimite;

	
    // carga de tamanho de um bloco
	  if(numMats <= E * 10) {
      numMatResto = 1;
      numThreads = E;
      numBlocks = 1;
    }
    else {
      const int numMatThreads = 3; // 3 foi escolhido para que numthreads seja maior multiplo de E(tamanho de cada matriz) e menor que um warp(32)
      numThreads = E * numMatThreads; 
      int espacoTrabThre = 10 * numThreads; //cada thread devera comparar ate E * 10 matrizes
      numBlocks = E * numMats / espacoTrabThre;
      numMatResto = numBlocks * numMatThreads;
    }

    posLimite = numMats * E;
    jump = numBlocks * numThreads;
	  os_menores<<<numBlocks, numThreads>>>(d_matrizes, posLimite, jump);
    cudaDeviceSynchronize();

    menorMatriz(d_matrizes, numMatResto);
	}
}


void encontraMenorMatriz(int* matrizes) {
  int tam = numMatrizes * E * sizeof(int);
  int *d_matrizes;

  // Alloc space for device copies of a, b, c
  cudaMalloc((void **) &d_matrizes, tam);

  // Copy inputs to device
  cudaMemcpy(d_matrizes, matrizes, tam, cudaMemcpyHostToDevice);

  // encontra menor matriz
  menorMatriz(d_matrizes, numMatrizes);
  
  // Copy result back to host
  cudaMemcpy(matrizes, d_matrizes, tam, cudaMemcpyDeviceToHost);

  cudaFree(d_matrizes);  
}


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

    encontraMenorMatriz(matrizes);
    leitura(matrizes, 1);



    // leitura(get_min(mat, 0, qtde));
    free(matrizes);
    return EXIT_SUCCESS;
  }
}

