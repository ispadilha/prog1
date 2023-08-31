#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int aleat (int min, int max){
    int tamanho = max - min;
    int x = (rand() % (tamanho + 1));
    x = x + min;

    /* A operação módulo retorna um resto de divisão,
    que estará dentro do intervalo correspondente a (tamanho - 1).
    Para corrigir isto, calculo o módulo por (tamanho + 1).
    Isto sorteia um número entre 0 e o tamanho. Por isso, somo (x + min).
    Assim, o sorteio será entre min e max. */

    return x;
}

int mdc(int a, int b){
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }

    /* O algoritmo de Euclides mantém um laço de repetição enquanto "b" não for zero.
    A cada iteração, atualiza "a" com o valor que estava em "b", e atualiza "b" com o resto da divisão.
    Quando o resto for zero, a repetição termina. E o resultado, (ou seja, o MDC) estará armazenado em "a". */

    return a;
}

int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);

    /* Aproveitando a função MDC. */

    return x;
}

struct racional simplifica_r (struct racional r){
    if (r.valido == 0) return r;

    /* Se o racional "r" fornecido for inválido (com denominador zero), a função não tem o que fazer,
    além de devolver o mesmo racional sem operar nada */

    int mdc_r = mdc(r.num, r.den);
    r.num = (r.num / mdc_r);
    r.den = (r.den / mdc_r);

    /* Aproveitei a função criada anteriormente, para o cálculo do MDC.
    A função simplifica o racional recebido através da divisão de ambos, numerador e denominador, pelo MDC entre os dois. */

    if((r.num < 0) && (r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    /* Se ambos, numerador e denominador, forem negativos, deverá retornar um positivo. */

    if((r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    /* Se apenas o denominador for negativo, o sinal deve migrar para o numerador. */

    return r;
}

struct racional cria_r (int numerador, int denominador){
    struct racional r;
    r.num = numerador;
    r.num = denominador;

    if(denominador != 0){
        r.valido = 1;
    } else {
        r.valido = 0;
    }

    /* Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando como inválido. */

    return r;
}

struct racional sorteia_r (int n){
    int den;
    do {
        den = (rand() % n);
    } while ( den == 0 ) ;

    /* Um laço de repetição assegura que o valor do denominador seja diferente de zero. */

    int num = (rand() % n);
    struct racional r = cria_r(num, den);

    /* Usei variáveis locais de inteiros para numerador e para denominador,
    para poder usar a função anterior, de criação de um número racional.  */

    return r;
}

void imprime_r (struct racional r){
    if (!valido_r(r)){
        printf("INVALIDO");
        return;
    } else {
        simplifica_r(r);
    }

    if ((r.num == 0) || (r.den == 1)){
        printf("%d", r.num);
        return;
    }

    if (r.num == r.den) {
        printf("1");
        return;
    }

    printf("%d/%d", r.num, r.den);
    return;
}

int valido_r (struct racional r){

    /* Um racional eh invalido se o denominador for nulo */
    
    if (r.den == 0){
        return 0;
    } else {
        return 1;
    }
}

struct racional soma_r (struct racional r1, struct racional r2) {
    struct racional resultado;
   
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) + ((d/r2.den) * r2.num);

    resultado.num = n;
    resultado.den = d;

    simplifica_r(resultado);

    resultado.valido = valido_r(resultado);

    return resultado;
}

struct racional subtrai_r (struct racional r1, struct racional r2) {
    struct racional resultado;
   
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) + ((d/r2.den) * r2.num);

    resultado.num = n;
    resultado.den = d;

    simplifica_r(resultado);

    resultado.valido = valido_r(resultado);
    
    return resultado;
}

struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional resultado;

    resultado.num = (r1.num * r2.num);
    resultado.den = (r1.den * r2.den);

    simplifica_r(resultado);

    resultado.valido = valido_r(resultado);

    return resultado;
}

struct racional divide_r (struct racional r1, struct racional r2){
    struct racional resultado;

    resultado.num = (r1.num * r2.den);
    resultado.den = (r1.den * r2.num);

    simplifica_r(resultado);

    resultado.valido = valido_r(resultado);

    return resultado;
}