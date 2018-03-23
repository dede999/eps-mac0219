/**
 * @aluno André Luiz Abdalla Silveira -- 8030353
 * @aluno Mauricio Luiz Cardoso -- 6796479
 * Mini Ep 2 -- MAC 0219
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VAZIO 0 
#define SAPO 1
#define RA -1
/**
 * Vetor que representa a lagoa
 * * 1 sapo
 * * -1 rã
 * * 0 pedra vazia
 */
int * lagoa;  

int pedras;
int tam_lagoa;
int cont = 0; /* representa a quantidade de vezes que um animal não se moveu */

void movimentando (void * a) {
    int spot = (int)a;
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Número de argumentos inválido, necessário 2 argumentos\n");
	printf("Formato de entrada: ./executavel numerosapos numeroras );
    }
    pthread_t *animais;
    int sapos = atoi(argv[1]);
    int ras = atoi (argv[2]);

    tam_lagoa = ras + sapos + 1;



    lagoa = malloc(tam_lagoa * sizeof(int));
    animais = malloc((ras + sapos) * sizeof(pthread_t));



    free(lagoa);
    free(animais);
}
