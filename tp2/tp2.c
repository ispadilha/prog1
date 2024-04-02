#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int main() {
    // Inicializando a semente randômica:
    srand(0);

    int n, max;
    
    // Assegurando que 0 < n < 100 e 0 < max < 30 conforme especificação:
    do
    {scanf("%d", &n);
    scanf("%d", &max);}
    while((n <= 0 && n >= 100) && (max <= 0 && max >= 30));

    for (int i = 1; i <= n; i++) {
        // Imprimindo o valor de i para mostrar a iteração:
        printf("%d: ", i);

        // Sorteando os dois racionais:
        struct racional r1 = sorteia_r(max);
        struct racional r2 = sorteia_r(max);

        // Imprimindo-os alternadamente com espaços em branco, conforme especificação, e também para melhor visualização:
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

        struct racional soma;
        soma_r(r1, r2, &soma);

        struct racional subtracao;
        subtrai_r(r1, r2, &subtracao);

        struct racional multiplicacao;
        multiplica_r(r1, r2, &multiplicacao);

        struct racional divisao;
        int divisao_valida = divide_r(r1, r2, &divisao);

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