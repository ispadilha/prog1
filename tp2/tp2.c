/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* Tamanho máximo do vetor: */
#define TMAX 100

/* Valor máximo de numerador e denominador para os números racionais utilizados: */
#define VMAX 10

int main() {
     /* Inicializando a semente randômica: */
    srand(0);

    /* Declarando variáveis que serão usadas como índices em laços de repetição: */
    int i = 0, j = 0, k = 0;

    /* e a variável do tipo inteiro que receberá do usuário o tamanho do vetor de racionais: */
    int n;
    
    printf("Digite um valor para n (0 < n < %d): ", TMAX);
    scanf("%d", &n);

    if (n <= 0 || n >= TMAX) {
        printf("\nO valor inserido está fora do intervalo permitido!\n");
        return 1;
    }

    /* Criando um vetor de n racionais: */
    struct racional vetor[n];

    for (i = 0; i < n; i++) {
        vetor[i] = sorteia_r(VMAX);
    }

    for (i = 0; i < n; i++) {
        imprime_r(vetor[i]);
    }

    /* Quebras de linha após impressões do vetor, conforme enunciado: */
    printf("\n");

    /* Filtrando racionais inválidos, usando a segunda variável de índice;
    E usando um novo vetor para não manipular o vetor original, aqui de dentro da função main,
    evitando assim uma violação de Tipo Abstrato de Dados: */

    struct racional vetor_validos[TMAX];
    for (i = 0; i < n; i++) {
        if (valido_r(vetor[i])) {
            vetor_validos[j] = vetor[i];
            j++;
        }
    }
   
    for (i = 0; i < j; i++) {
        imprime_r(vetor_validos[i]);
    }

    printf("\n");

    /* Ordenando o vetor, utilizando o algoritmo Selection Sort: */
    for (i = 0; i < j - 1; i++) {
        int i_menor = i;

        for (k = i + 1; k < j; k++) {
            if (compara_r(vetor_validos[k], vetor_validos[i_menor]) < 0) {
                i_menor = k;
            }
        }

        if (i_menor != i) {
            struct racional temp = vetor_validos[i];
            vetor_validos[i] = vetor_validos[i_menor];
            vetor_validos[i_menor] = temp;
        }
    }

    for (i = 0; i < j; i++) {
        imprime_r(vetor_validos[i]);
    }

    printf("\n");

    /* Para calcular a soma de todos os elementos do vetor:
    Inicialmente, declaramos um racional inicializado em 0;
    ou seja, 0/1: */
    struct racional soma = cria_r(0, 1);
    struct racional temp = cria_r(0, 1);

    for (i = 0; i < j; i++) {
        if (soma_r(soma, vetor_validos[i], &temp)) {
            soma = temp;
            simplifica_r(&soma);
        }
    }

    printf("Soma de todos os elementos: ");
    imprime_r(soma);
    printf("\n");

    return 0;
}

