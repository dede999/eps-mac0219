/**
 * @aluno André Luiz Abdalla Silveira -- 8030353
 * @aluno Mauricio Luiz Cardoso -- 0000000
 * Mini Ep 2 -- MAC 0219
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

int main (){
    pthread_t * animais;
    int ras, sapos;
    scanf("%d", &ras);
    scanf("%d", &sapos);
    tam_lagoa = ras + sapos + 1;

    lagoa = malloc(tam_lagoa * sizeof(int));
    animais = malloc((ras + sapos) * sizeof(pthread_t));



    free(lagoa);
    free(animais);
}
