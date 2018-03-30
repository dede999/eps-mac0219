/**
 * @aluno André Luiz Abdalla Silveira -- 8030353
 * @aluno Mauricio Luiz Cardoso -- 6796479
 * Mini Ep 2 -- MAC 0219
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct pedra {
    int posPedra;   /* posicao pedra na lagoa */
    int tipoAnimal; /* identifica sapo, ra ou pedra vazia*/
    pthread_t animalThread; /* thread do animal, se for null, é uma pedra vazia */
} Pedra;

#define VAZIO -1
#define SAPO 1
#define RA 2

Pedra *lagoa;  /* pode ser um vetor de Animal ou inteiro */

int MAX;
int threadsAtivas = 0;
int tam_lagoa;
int cont = 0; /* representa a quantidade de vezes que um animal não se moveu */
pthread_mutex_t mutex;

void trocaAnimais (int posPedra1, int posPedra2) {
    int tipoAnimalAux;

    tipoAnimalAux = lagoa[posPedra1].tipoAnimal;
    lagoa[posPedra1].tipoAnimal = lagoa[posPedra2].tipoAnimal;
    lagoa[posPedra2].tipoAnimal = tipoAnimalAux;
}


void mostraLagoa() {
    int i;
    for (i = 0; i < tam_lagoa; ++i) {
        if (lagoa[i].tipoAnimal == RA) printf("RA ");
        else if (lagoa[i].tipoAnimal == SAPO) printf("SAPO ");
        else printf("VAZIO ");
    }
    printf("\n");
}

void *movimentando (void * pedra) {
    int i = 0;
    Pedra * pedraComAnimal = (Pedra *) pedra;
    int posPedra = pedraComAnimal->posPedra;

    while(threadsAtivas < tam_lagoa) { 
        i++;
    }

    while(cont < MAX) {
        pthread_mutex_lock(&mutex);
        if (pedraComAnimal->tipoAnimal == RA) {
            if (posPedra + 1 < tam_lagoa && lagoa[posPedra + 1].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra + 1);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                mostraLagoa();
            } 
            else if (posPedra + 2 < tam_lagoa && lagoa[posPedra + 2].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra + 2);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                mostraLagoa();
            } 
            else {
                cont ++;
            }
        } 
        else if (pedraComAnimal->tipoAnimal == SAPO) {
            if (posPedra - 1 >= 0 && lagoa[posPedra - 1].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra - 1);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                mostraLagoa();
            } 
            else if (posPedra - 2 >= 0 && lagoa[posPedra - 2].tipoAnimal == VAZIO) {
                trocaAnimais(posPedra, posPedra - 2);
                cont = 0; /* reseta contador, pois ocorreu pulo */
                mostraLagoa();
            } 
            else {
                cont ++;
            }
        }
        pthread_mutex_unlock(&mutex);
    }

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
        int i;

        tam_lagoa = ras + sapos + 1;
        MAX = tam_lagoa * 100000;
        lagoa = malloc(tam_lagoa * sizeof(Pedra));

        preparaLagoa(ras);
        mostraLagoa();

        for (i = 0; i < tam_lagoa; ++i) { /*rãs começam a pular*/
            if (pthread_create(&lagoa[i].animalThread, NULL, movimentando, (void *) &lagoa[i])) {
                printf("Erro ao criar uma thread SAPO\n");
                exit(1);
            }
            threadsAtivas++;
        }


        for (i = 0; i < tam_lagoa; ++i) {
            if (pthread_join(lagoa[i].animalThread, NULL)) {
                printf("Erro ao finalizar uma das thread\n");
                exit(1);
            }
        }

        free(lagoa);
        return 0;
    }
}
