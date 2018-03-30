/**
 * @aluno André Luiz Abdalla Silveira -- 8030353
 * @aluno Mauricio Luiz Cardoso -- 6796479
 * Mini Ep 2 -- MAC 0219
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*#define LENGTH(x) (sizeof(x)/sizeof(x[0]))*/

typedef struct pedra {
    int id; /* identifier de animal ou pedra*/
    int n_pedra; /* # da casa (ou pedra) em que o animal está */
} Pedra;

#define VAZIO 0 
#define SAPO 1
#define RA -1
#define MAX 5000
/**
 * Vetor que representa a lagoa
 * * 1 sapo
 * * -1 rã
 * * 0 pedra vazia
 */
Pedra *lagoa;  /* pode ser um vetor de Animal ou inteiro */

int pedras;
int tam_lagoa;
int cont = 0; /* representa a quantidade de vezes que um animal não se moveu */
pthread_mutex_t mutex;

void movimentando (void * a) {
    Pedra spot = (Pedra) a;
    while(cont < MAX) {
        pthread_mutex_lock(&mutex);
        // fazendo a "magica"
        if (spot.id)
        pthread_mutex_unlock(&mutex);
    }
    printf("Animal %d na casa %d\n", spot.id, spot.n_pedra);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Número de argumentos inválido, necessário 2 argumentos\n");
	    printf("Formato de entrada: ./executavel numerosapos numeroras ");
        return 1;
    }
    else {
        pthread_t *pedra;
        int sapos = atoi (argv[1]);
        int ras = atoi (argv[2]);
        int i, j = 0, k, ind, qtde_thread = 0; /* contadores */

        tam_lagoa = ras + sapos + 1;

        lagoa = malloc(tam_lagoa * sizeof(Pedra));
        pedra = malloc((ras + sapos) * sizeof(pthread_t));

        for (i = 0; i < ras; ++i) { /*alocando rãs no vetor de pedras e pthreads*/
            lagoa[i].n_pedra = i;        
            lagoa[i].id = RA;
            if (pthread_create(&pedra[qtde_thread++], NULL, movimentando, (void *) &lagoa[i])) {
                printf("Erro ao criar uma thread RA\n");
                exit(1);
            }
            
        }

        lagoa[i].id = VAZIO;
        lagoa[i].n_pedra = i;


        i = tam_lagoa -  1;
        while (j < sapos) {  /*alocando sapos no vetor de pedras e pthreads*/
            ind = i - j;
            j++;
            lagoa[ind].id = SAPO;
            lagoa[ind].n_pedra = ind;
            if (pthread_create(&pedra[qtde_thread++], NULL, movimentando, (void *) &lagoa[ind])) {
                printf("Erro ao criar uma thread SAPO\n");
                exit(1);
            }
        }
        for (k = 0; k < (ras + sapos); ++k) {
            if (pthread_join(pedra[k], NULL)) {
                printf("Erro ao finalizar uma das thread\n");
                exit(1);
            }
        }

        free(lagoa);
        free(pedra);
        return 0;
    }
}
