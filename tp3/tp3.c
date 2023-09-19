/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

int le_n_valido(){
    int n;

    do {
        scanf("%d", &n);
    } while (n < 1 || n > MAX);

    return n;
}

void imprime_vetor(int i, int n, struct racional **v){
    for (i = 0; i < n; i++) {
        imprime_r(v[i]);
    }

    printf("\n");
}

void imprime_soma(int i, int j, struct racional **v_validos){
    /* Para calcular a soma de todos os elementos do vetor:
    Inicialmente, declaramos um racional inicializado em 0;
    ou seja, 0/1: */
    struct racional *soma = cria_r(0, 1);
    struct racional *temp = cria_r(0, 1);

    for (i = 0; i < j; i++) {
        if (soma_r(soma, v_validos[i], temp)) {
            soma = temp;
            simplifica_r(soma);
        }
    }

    printf("Soma de todos os elementos: ");
    imprime_r(soma);
    printf("\n");
}

int main() {
    struct racional **v;
    struct racional **v_validos;
    int i, j, n;
    long int a, b;

    /* Exige um n valido entre 1 e MAX */
    n = le_n_valido();

    v = (struct racional **)malloc(sizeof(struct racional *) * n);
    if (!v) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    v_validos = ((struct racional **)malloc(sizeof(struct racional *) * n));
    if (!v_validos) {
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

    /* Imprime cada racional seguido de um espaco, e pula uma linha apos imprimir o vetor inteiro */
    imprime_vetor(i, n, v);

    /* Filtrando racionais inválidos, usando a segunda variável de índice e um novo vetor */
    for (i = 0; i < n; i++) {
        if (valido_r(v[i])) {
            v_validos[j] = v[i];
            j++;
        }
    }

    imprime_vetor(i, n, v_validos);

    //Ordenar vetor

    //Calcular e imprimir a soma de todos os racionais do vetor
    imprime_soma(i,j, v_validos);

    // Liberando a memória alocada para os racionais
    for (i = 0; i < n; i++) {
        destroi_r(v[i]);
    }

    // Liberando o vetor de ponteiros
    free(v);

    return 0;
}
