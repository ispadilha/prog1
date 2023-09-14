/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

int main (){
    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */

    int i, n;
    long int a, b;

    do(
        scanf("%d", &n)
    );
    while (
        n < 1 || n > MAX
    );
    
    v = malloc (sizeof(struct racional*)*n);
    
    for (i = 0; i<n; i++){
        /* usar a funcao cria_r */
        scanf("%ld %ld", &a, &b);
        v[i] = cria_r(a, b);
    }

    for (i=0; i<n; i++){
        imprime_r(v[i]);
    }
    
    printf("\n");

    return 0;

}
