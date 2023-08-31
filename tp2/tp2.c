/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int main() {
     /* Inicializando a semente randômica: */
    srand(0);

    /* Declarando variáveis que serão usadas como índices em laços de repetição: */
    int i = 0, j = 0, k = 0;

    int n;
    printf("\nDigite um valor para n (0 < n < 100): ");
    scanf("%d", &n);

    if (n <= 0 || n >= 100) {
        printf("\nO valor inserido está fora do intervalo permitido!\n");
        return 1;
    }

    /* Criando um vetor de n racionais: */
    struct racional vetor[n];

    for (i = 0; i < n; i++) {
        vetor[i] = sorteia_r(100);
    }

    for (i = 0; i < n; i++) {
        imprime_r(vetor[i]);
    }

    /* Filtrando racionais inválidos, usando a segunda variável de índice: */
    for (i = 0; i < n; i++) {
        if (valido_r(vetor[i])) {
            vetor[j] = vetor[i];
            j++;
        }
    }

    /* O novo vetor poderá ser menor, devido a eliminações de elementos inválidos; por isso o laço irá até o "j" encontrado acima: */
    for (i = 0; i < j; i++) {
        imprime_r(vetor[i]);
    }

    /* Ordenando o vetor, utilizando o algoritmo Selection Sort: */
    for (i = 0; i < j - 1; i++) {
        int i_menor = i;

        for (k = i + 1; k < j; k++) {
            if (compara_r(vetor[k], vetor[i_menor]) < 0) {
                i_menor = k;
            }
        }

        if (i_menor != i) {
            struct racional temp = vetor[i];
            vetor[i] = vetor[i_menor];
            vetor[i_menor] = temp;
        }
    }
    /* O algoritmo Selection Sort garante que, a cada iteração, o menor elemento do vetor estará em sua posição definitiva. */

    for (i = 0; i < j; i++) {
        imprime_r(vetor[i]);
    }

    // Calculando e imprimindo a soma dos elementos do vetor
    struct racional soma = cria_r(0, 1);
    for (i = 0; i < j; i++) {
        struct racional temp;
        if (soma_r(soma, vetor[i], &temp)) {
            soma = temp;
        }
    }

    printf("\nSoma de todos os elementos: ");
    imprime_r(soma);
    printf("\n");

    return 0;
}

