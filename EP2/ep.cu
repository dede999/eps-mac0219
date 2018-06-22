/** 
* André Luiz Abdalla Silveira 8030353
* Mauricio Luiz Cardoso 6796479
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


__global__ void os_menores(int *d_matrizes, int numMats, int jump) {
  int indexAtual = indexIni = threadIdx.x + blockIdx.x * blockDim.x;
  int tamMatriz = 9;

  if(index < numMats * tamMatriz) {

  }
  else {
    return;
  }

}

/* Imprime todas as matrizes de dimensão ExE contidas em matrizes*/
void leitura (int *matrizes) {
  int i, k;
  for (i = 0; i < numMatrizes * linhaElementos; i++) {
    for (k = 0; k < linhaElementos; k++) 
      printf("%d\t", *(matrizes++));
    printf("\n");
    if((i+1) % linhaElementos == 0)
      printf("********************\n");
  }
}


void menorMatriz(int *d_matrizes, int numMats) {
  int numBlocks = numMats / 30;
  int numMatResto;
  int numThreads = 27;




  os_menores<<<numBlocks, numThreads>>>(d_matrizes, numMats, numThreads * numBlocks);



  // if((numMatResto = numMats % 30) != 0) {
  //   // caso com chamada a mais

  // }



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
    return EXIT_SUCCESS;
  }
}

