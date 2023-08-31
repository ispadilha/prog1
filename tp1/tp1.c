#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int main() {
    srand(0);  // Inicializando a semente randômica

    int n, max;
    scanf("%d", &n);  // Lê o valor de n
    scanf("%d", &max);  // Lê o valor de max

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);  // Imprime o valor de i para mostrar a iteração

        struct racional r1 = sorteia_r(max);  // Sorteia o primeiro racional
        struct racional r2 = sorteia_r(max);  // Sorteia o segundo racional

        imprime_r(r1);  // Imprime r1
        printf(" ");
        imprime_r(r2);  // Imprime r2
        printf(" ");

        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        struct racional soma = soma_r(r1, r2);
        struct racional subtracao = subtrai_r(r1, r2);
        struct racional multiplicacao = multiplica_r(r1, r2);
        struct racional divisao = divide_r(r1, r2);

        if (!valido_r(divisao)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        imprime_r(soma);
        printf(" ");
        imprime_r(subtracao);
        printf(" ");
        imprime_r(multiplicacao);
        printf(" ");
        imprime_r(divisao);
        printf("\n");
    }

    return 0;
}
