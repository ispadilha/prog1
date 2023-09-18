/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

int main() {
    struct racional **v;
    int i, n;
    long int a, b;

    do {
        scanf("%d", &n);
    } while (n < 1 || n > MAX);

    v = (struct racional **)malloc(sizeof(struct racional *) * n);
    if (!v) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%ld %ld", &a, &b);
        v[i] = cria_r(a, b);
        if (!v[i]) {
            printf("Erro na alocação de memória para o racional %d.\n", i);
            return 1;
        }
    }

    for (i = 0; i < n; i++) {
        imprime_r(v[i]);
    }

    // Liberando a memória alocada para os racionais
    for (i = 0; i < n; i++) {
        destroi_r(v[i]);
    }

    // Liberando o vetor de ponteiros
    free(v);

    return 0;
}
