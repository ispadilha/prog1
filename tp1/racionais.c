#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int aleat (int min, int max){
    int tamanho = max - min;

    // O operador módulo por (tamanho + 1) retornará um valor entre 0 e tamanho, inclusive:
    int x = (rand() % (tamanho + 1));
    
    // Somando (x + min) ao valor acima, o sorteio será entre min e max:
    x = x + min;

    return x;
}

int mdc (int a, int b){
    // Utilizando o algoritmo de Euclides:
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }

    return a;
}

int mmc (int a, int b){
    // Utilizando o MDC calculado anteriormente:
    int x = (a*b)/mdc(a,b);

    return x;
}

struct racional simplifica_r (struct racional r){
    // A função simplifica o racional recebido através da divisão de ambos, numerador e denominador, pelo MDC entre os dois:
    int mdc_r = mdc(r.num, r.den);
    r.num = (r.num / mdc_r);
    r.den = (r.den / mdc_r);

    // Se numerador e denominador forem negativos, o racional retornado será positivo:
    if((r.num < 0) && (r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    // Se apenas o denominador for negativo, o sinal deve migrar para o numerador: 
    if((r.den < 0) && (r.num > 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    return r;
}

struct racional cria_r (int numerador, int denominador){
    struct racional r;
    r.num = numerador;
    r.den = denominador;

    // Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando o racional criado como inválido:
    if(denominador != 0){
        r.valido = 1;
    } else {
        r.valido = 0;
    }

    return r;
}

struct racional sorteia_r (int max){
    // Neste programa, o valor de min será sempre igual a 0, conforme especificação:
    int num = aleat(0, max);
    int den = aleat(0, max);

    struct racional r = cria_r(num, den);

    return r;
}

void imprime_r (struct racional r){
    // O racional só poderá ser simplificado se não for inválido, ou seja, se o denominador for diferente de 0:
    if (!valido_r(r)){
        printf("INVALIDO");
        return;
    } else {
        r = simplifica_r(r);
    }

    // Casos em que pode-se omitir o denominador:
    if ((r.num == 0) || (r.den == 1)){
        printf("%d", r.num);
        return;
    }

    printf("%d/%d", r.num, r.den);
    return;
}

int valido_r (struct racional r){
    // Um racional é inválido se o denominador for igual a 0:
    if (r.den == 0 || r.valido == 0){
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

    resultado.valido = valido_r(resultado);

    simplifica_r(resultado);

    return resultado;
}

struct racional subtrai_r (struct racional r1, struct racional r2) {
    struct racional resultado;
   
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) - ((d/r2.den) * r2.num);

    resultado.num = n;
    resultado.den = d;

    resultado.valido = valido_r(resultado);

    simplifica_r(resultado);
    
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

    if (r2.num == 0) {
        resultado.valido = 0;
    } else {
        resultado.valido = 1;
        simplifica_r(resultado);
    }
    
    return resultado;
}