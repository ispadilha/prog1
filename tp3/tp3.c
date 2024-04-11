#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

void elimina_invalidos(struct racional **v, int *n){
    int i;
    for (i = 0; i < *n; i++){
        if (denominador_r(v[i]) == 0){
            v[i] = v[*n];
            n--;
        }
    }
}

void imprime_vetor(struct racional **v, int n){
    int i;
    for (i = 0; i < n; i++)
    {
        imprime_r(v[i]);
        printf(" ");
    }
    printf("\n");
}

int main (){
    int n, i;
    long int num_lido, den_lido;

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */

    /* Assegurando que 0 < n < 100 conforme especificação: */
    do {
        scanf("%d", &n);
        if(n <= 0 || n >= 100){
            printf("O valor de n precisa estar entre 0 e 100. Tente novamente: ");
        }
    } while (n <= 0 || n >= 100);

    v = malloc(n * sizeof(struct racional));

    if (v == NULL){
        return 1;
    }

    for (i = 0; i < n; i++){
        scanf("%ld %ld", &num_lido, &den_lido);
        v[i] = cria_r(num_lido, den_lido);
    }

    imprime_vetor(v, n);

    elimina_invalidos(v, &n);

    imprime_vetor(v, n);

    return 0;
}
