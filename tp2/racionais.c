#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* retorna um numero aleatorio entre min e max, inclusive. */
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

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
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

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);

    /* Aproveitando a função MDC. */

    return x;
}

struct racional cria_r (int numerador, int denominador){
    struct racional r;
    r.num = numerador;
    r.den = denominador;

    if(denominador != 0){
        r.valido = 1;
    } else {
        r.valido = 0;
    }

    /* Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando como inválido. */

    return r;
}

int simplifica_r (struct racional *r){
    /* Retorna 0 caso receba um racional inválido. */
    if (r->valido == 0) return 0;
    
    /* Aproveitei a função criada anteriormente, para o cálculo do MDC.
    A função simplifica o racional recebido através da divisão de ambos, numerador e denominador, pelo MDC entre os dois. */
    int mdc_r = mdc(r->num, r->den);
    r->num = ((r->num) / mdc_r);
    r->den = ((r->den) / mdc_r);

    /* Se ambos, numerador e denominador, forem negativos, deverá retornar um positivo. */
    if((r->num < 0) && (r->den < 0)){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }

    /* Se apenas o denominador for negativo, o sinal deve migrar para o numerador. */
    if((r->den < 0)){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}

struct racional sorteia_r (int max){
    int den;
    do {
        den = (rand() % max);
    } while ( den == 0 ) ;

    /* Um laço de repetição assegura que o valor do denominador seja diferente de zero. */

    int num = (rand() % max);
    struct racional r = cria_r(num, den);

    /* Usei variáveis locais de inteiros para numerador e para denominador,
    para poder usar a função anterior, de criação de um número racional.  */

    return r;
}

/* Retorna o numerador de um racional */
int numerador_r (struct racional r){
    return r.num;
}

/* Retorna o denominador de um racional */
int denominador_r (struct racional r){
    return r.den;
}

int valido_r (struct racional r){

    /* Um racional eh invalido se o denominador for nulo */
    
    if (r.den == 0){
        return 0;
    } else {
        return 1;
    }
}

void imprime_r (struct racional r){
    if (!valido_r(r)){
        printf("INVALIDO");
        return;
    } else {
        simplifica_r(&r);
    }

    if ((r.num == 0) || (r.den == 1)){
        printf("%d ", r.num);
        return;
    }

    if (r.num == r.den) {
        printf("1");
        return;
    }

    printf("%d/%d ", r.num, r.den);
    return;
}

int compara_r(struct racional r1, struct racional r2) {
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)) {
        return 0;
    }

    /* Usarei o MMC entre os denominadores, e com ele calcularei os novos numeradores, para poder comparar os dois racionais */
    int mmc_den = mmc(r1.den, r2.den);
    int num1 = r1.num * (mmc_den / r1.den);
    int num2 = r2.num * (mmc_den / r2.den);

    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
    /* Conforme o enunciado: */
    /* Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2 */
}


int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }
   
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) + ((d/r2.den) * r2.num);

    /* Uso "d" e "n" como variáveis para numerador e denominador, no escopo local;
    O denominador é o MMC entre as frações (números racionais), conforme a operação matemática correspondente */

    r3->num = n;
    r3->den = d;

    simplifica_r(r3);

    r3->valido = valido_r(*r3);

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }
   
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) - ((d/r2.den) * r2.num);

    /* Bastante semelhante à função de soma, tomando o cuidado devido com o sinal */

    r3->num = n;
    r3->den = d;

    simplifica_r(r3);

    r3->valido = valido_r(*r3);

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }

    r3->num = (r1.num * r2.num);
    r3->den = (r1.den * r2.den);

    simplifica_r(r3);

    r3->valido = valido_r(*r3);

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }

    r3->num = (r1.num * r2.den);
    r3->den = (r1.den * r2.num);

    simplifica_r(r3);

    r3->valido = valido_r(*r3);

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}