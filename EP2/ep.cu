/** 
* André Luiz Abdalla Silveira 8030353
* Mauricio Luiz Cardoso 0000000
* 
* Esse programa escrito em CUDA visa criar um algoritmo que gera uma redução
*	de matrizes. Cada matriz é representada por um vetor e todos estão 
*	reunidos num vetor de vetores. A ideia é fazer uma função que faz uma 
*	comparação entre vetores fazendo o mínimo de operações
*
*	Observação pro Mauricio (delete depois de ler): depois de passar um tempão
*	pensando numa solução mais elegante, eu percebi que o número de comparações
*	é o mesmo se compararmos com uma implemetação onde se contrapõem dois vetores
*	iniciais, e o resultante da comparação com o próximo, e por aí vai.
*	O que falta? 1- leitura de arquivos 2- fazer a parte de CUDA 3- corrigir eventuais
*									bugs
*/

#include <stdio.h>
#define E 9 // qtde de elementos de cada matriz
/*#define linhaTam 3 */

/* pedaço de código copaido da apresentação, deve ser alterado sob demanda */
__global__ void os_menores(int *a, int *b, int *c) {
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

void leitura (int *mat) {
	int i, j;
	for (i = 0; i < 3; i ++) {
		printf("\n");
		for (k = 0; k < 3; k ++) 
			printf("%d\t", mat[3 * i + k]);
		printf("\n");
	}
}

int * compara (int *a, int *b) { /* Muitas coisas copiadas dos slides 36 e 37 */
	int *resp, tam = E * sizeof(int);
	int *d_a, *d_b, *d_resp;
	
	// Alloc space for device copies of a, b, c
	cudaMalloc((void **) &d_a, tam);
	cudaMalloc((void **) &d_b, tam);
	cudaMalloc((void **) &d_resp, tam);

	// Copy inputs to device
	cudaMemcpy(d_a, a, tam, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, tam, cudaMemcpyHostToDevice);

	// Launch add() kernel on GPU with N threads -- mudar o valor de N
	add<<<1,N>>>(d_a, d_b, d_resp);

	// Copy result back to host
	cudaMemcpy(resp, d_resp, tam, cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_resp);
	return resp;
}

int * get_min (int **mat, int ini, int fim) {
	int *parteA, *parteB;
	if (ini - fim > 1){ /* mais que 2 elementos*/
		meio = (ini + fim)/2;
		parteA = get_min(mat, ini, meio);
		parteB = get_min(mat, meio + 1, fim);
		return compara(parteA, parteB);
	}else if (ini - fim == 1){ /* 2 elementos */
		return compara(mat[ini], mat[fim]);
	}
	else {
		return mat[ini];
	}
}

void apaga (int **mat){
	int i;
	int linhas = (sizeof(mat)/sizeof(int *));
	for (i = 0; i < linhas; ++i) {
		free(mat[i]);
	}
	free(mat);
}

int** alocaMatrizes(int numMatrizes) {
	int** mat = (int *) malloc(numMatrizes * sizeof(int *));
	
	for (int i = 0; i < numMatrizes; i ++){
		mat[i] = (int) malloc(E * sizeof(int));
	}
	return mat;
}

double** alocaMatrizesArquivo(FILE *arq){
    int numMatrizes, l, c;
    char* asteriscos;
    double valor;
    double **matrizes;

    fscanf(arq, "%d", &numMatrizes);
    matrizes = alocaMatrizes(numMatrizes);
    
    for(int i = 0; i < numMatrizes; i++) {
    	fscanf(arq, "%s", &asteriscos); //pula a linha de asteriscos
    	for(int j = 0; j < E; j++)
        	fscanf(arq, "%d", &matrizes[i][j]);
    }
    return matriz;
}


int main (int argc, char* argv[]) {
	if(argc != 2) {
		printf("Argumento do programa: nome do arquivo\n");
	}
	else {
		int qtde;
		int **mat;
		FILE *entrada;
		int i; # contador

		entrada =  fopen(argv[1], "r");
		if (entrada == NULL) {
			printf("Deu ruim pra abrir o arquivo");
			return EXIT_FAILURE;
		}


		fclose(entrada);
		leitura(get_min(mat, 0, qtde));
		apaga(mat);
	}
}
