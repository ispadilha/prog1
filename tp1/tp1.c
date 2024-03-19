#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int main() {
    // Inicializando a semente randômica:
    srand(0);

    int n, max;
    
    scanf("%d", &n);
    scanf("%d", &max);

    for (int i = 1; i <= n; i++) {
        // Imprimindo o valor de i para mostrar a iteração:
        printf("%d: ", i);

        // Sorteando os dois racionais, e depois imprimindo-os alternadamente com espaços em branco, para melhor visualização:
        struct racional r1 = sorteia_r(max);
        struct racional r2 = sorteia_r(max);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        printf(" ");

        // Verificando se pelo menos um dos dois racionais sorteados é inválido, ou seja, se possui denominador igual a 0:
        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        // Efetuando as operações:
        struct racional soma = soma_r(r1, r2);
        struct racional subtracao = subtrai_r(r1, r2);
        struct racional multiplicacao = multiplica_r(r1, r2);
        struct racional divisao = divide_r(r1, r2);

        // Verificando se a divisão entre os dois racionais é inválida, ou seja, se o racional no denominador é igual a 0:
        if (!valido_r(divisao)) {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        // Imprimindo os resultados das operações:
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
