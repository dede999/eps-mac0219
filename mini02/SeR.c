/**
 * @aluno André Luiz Abdalla Silveira -- 8030353
 * @aluno Mauricio Luiz Cardoso -- 6796479
 * Mini Ep 2 -- MAC 0219
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

typedef struct Animais {
    int id; /* identifier */
    int n_pedra; /* # da casa (ou pedra) em que o animal está */
} Animal;

#define VAZIO 0 
#define SAPO 1
#define RA -1
/**
 * Vetor que representa a lagoa
 * * 1 sapo
 * * -1 rã
 * * 0 pedra vazia
 */
Animal * lagoa;  /* pode ser um vetor de Animal ou inteiro */

int pedras;
int tam_lagoa;
int cont = 0; /* representa a quantidade de vezes que um animal não se moveu */

void movimentando (void * a) {
    Animal spot = (Animal)a;
    printf("Animal %d na casa %d", spot.id, spot.n_pedra);
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Número de argumentos inválido, necessário 2 argumentos\n");
	    printf("Formato de entrada: ./executavel numerosapos numeroras ");
        return 1;
    }
    pthread_t *animais;
    int sapos = atoi (argv[1]);
    int ras = atoi (argv[2]);
    int i, j = 0, k, ind, qtde_thread = 0; /* contadores */

    tam_lagoa = ras + sapos + 1;

    lagoa = malloc(tam_lagoa * sizeof(Animal));
    animais = malloc((ras + sapos) * sizeof(pthread_t));

    for (i = 0; i < ras + 1; ++i) {
        lagoa[i].n_pedra = i;
        if (i == ras) {
            lagoa[i].id = VAZIO;
        }
        else {
            lagoa[i].id = RA;
            if (pthread_create(animais[qtde_thread ++], lagoa[i], movimentando, NULL)) {
                printf("Erro ao criar uma thread RA\n");
                exit(1);
            }
        }
    }
    i = tam_lagoa -  1;
    while (j < sapos) {
        ind = i - j;
        j ++;
        lagoa[ind].id = SAPO;
        lagoa[ind].n_pedra = ind;
        if (pthread_create(&animais[qtde_thread ++], lagoa[ind], movimentando, NULL)) {
            printf("Erro ao criar uma thread SAPO\n");
            exit(1);
        }
    }
    for (k = 0; k < (ras + sapos); ++k) {
        if (pthread_join(animais[k], NULL)) {
            printf("Erro ao finalizar uma das thread\n");
            exit(1);
        }
    }

    free(lagoa);
    free(animais);
    return 0;
}
