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
    int posPedra;   /* posicao pedra na lagoa */
    int tipoAnimal; /* identifica sapo, ra ou pedra vazia*/
    pthread_t animalThread; /* thread do animal, se for null, é uma pedra vazia */
} Pedra;

#define VAZIO -1
#define SAPO 1
#define RA 2
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

void trocaAnimais (int posPedra1, int posPedra2) {
    int  tipoAnimalAux;
    pthread_t animalThreadAux;

    tipoAnimalAux = lagoa[posPedra1].tipoAnimal;
    lagoa[posPedra1].tipoAnimal = lagoa[posPedra2].tipoAnimal;
    lagoa[posPedra2].tipoAnimal = tipoAnimalAux;

    animalThreadAux = lagoa[posPedra1].animalThread;
    lagoa[posPedra1].animalThread = lagoa[posPedra2].animalThread;
    lagoa[posPedra2].animalThread = animalThreadAux;
}

void mostra (int tipoAnimal){
    if (tipoAnimal == RA) printf("RA ");
    else if (tipoAnimal == SAPO) printf("SAPO ");
    else printf("VAZIO ");
}

void debug() {
    int i;
    for (i = 0; i < tam_lagoa; ++i) {
        mostra(lagoa[i].tipoAnimal);
    }
    printf("\n");
}

void *movimentando (void * pedra) {
    Pedra * pedraComAnimal = (Pedra *) pedra;
    int posPedra = pedraComAnimal->posPedra;
    while(cont < MAX) {
        pthread_mutex_lock(&mutex);
        if (pedraComAnimal->tipoAnimal == RA) {
            if (posPedra + 1 < tam_lagoa && lagoa[posPedra + 1].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra + 1);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                debug();
            } 
            else if (posPedra + 2 < tam_lagoa && lagoa[posPedra + 2].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra + 2);                
                cont = 0; /* reseta contador, pois ocorreu pulo */
                debug();
            } 
            else {
                cont ++;
            }
        } 
        else if (pedraComAnimal->tipoAnimal == SAPO) {
            if (posPedra - 1 >= 0 && lagoa[posPedra - 1].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra - 1);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                debug();
            } 
            else if (posPedra - 2 >= 0 && lagoa[posPedra - 2].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra - 2);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                debug();
            } 
            else {
                cont ++;
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("Animal %d na casa %d\n", pedraComAnimal->tipoAnimal, pedraComAnimal->posPedra);
    pthread_exit(NULL);
}


void preparaLagoa(int ras) {
    int i = 0;
    for (i = 0; i < ras; ++i) { /*alocando rãs no vetor de pedras */
        lagoa[i].posPedra = i;
        lagoa[i].tipoAnimal = RA;        
    }

    lagoa[i].posPedra = i;
    lagoa[i].tipoAnimal = VAZIO;
    i++;

    for (; i < tam_lagoa; ++i) { /*alocando sapos no vetor de pedras */ 
        lagoa[i].posPedra = i;
        lagoa[i].tipoAnimal = SAPO;        
    }

}


int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Número de argumentos inválido, necessário 2 argumentos\n");
	    printf("Formato de entrada: ./executavel numerosapos numeroras ");
        return 1;
    }
    else {
        int sapos = atoi (argv[1]);
        int ras = atoi (argv[2]);
        int i, k; /* contadores */

        tam_lagoa = ras + sapos + 1;

        lagoa = malloc(tam_lagoa * sizeof(Pedra));


        preparaLagoa(ras);


        for (i = 0; i < ras; ++i) { /*rãs começam a pular*/
            if (pthread_create(&lagoa[i].animalThread, NULL, movimentando, (void *) &lagoa[i])) {
                printf("Erro ao criar uma thread RA\n");
                exit(1);
            }
            
        }        

        for (i++; i < tam_lagoa; ++i) { /*sapos começam a pular*/
            if (pthread_create(&lagoa[i].animalThread, NULL, movimentando, (void *) &lagoa[i])) {
                printf("Erro ao criar uma thread SAPO\n");
                exit(1);
            }
            
        }


/*        for (k = 0; k < (ras + sapos); ++k) {
            if (pthread_join(pedra[k], NULL)) {
                printf("Erro ao finalizar uma das thread\n");
                exit(1);
            }
        }*/

        free(lagoa);
        return 0;
    }
}
