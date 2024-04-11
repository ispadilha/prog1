#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

/* Retorna um número aleatório entre min e max, inclusive: */
int aleat (long int min, long int max){
    int tamanho = max - min;

    /* O operador módulo por (tamanho + 1) retornará um valor entre 0 e tamanho, inclusive: */
    int x = (rand() % (tamanho + 1));
    
    /* Somando (x + min) ao valor acima, o sorteio será entre min e max: */
    x = x + min;

    return x;
}

/* Calcula o MDC pelo método de Euclides, em sua versão recursiva: */
long int mdc (long int a, long int b) {
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

/* Calcula o MMC, utilizando o MDC calculado anteriormente: */
long int mmc (long int a, long int b){
    int x = (a*b)/mdc(a,b);
    return x;
}

void simplifica_r (struct racional *r) {
    /* A função simplifica o racional recebido através da divisão de ambos,
    numerador e denominador, pelo MDC entre os dois: */
    int mdc_r = mdc(r->num, r->den);
    r->num = (r->num / mdc_r);
    r->den = (r->den / mdc_r);

    /* Se numerador e denominador forem negativos, o racional retornado será positivo: */
    if (r->num < 0 && r->den < 0) {
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
    /* Se apenas o denominador for negativo, o sinal deve migrar para o numerador: */
    else if (r->den < 0 && r->num > 0) {
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
}

/* Seguem as implementações das funções definidas no racionais.h: */

struct racional *cria_r (long int numerador, long int denominador){
    struct racional *r = malloc(sizeof(struct racional));

    if (r == NULL){
        return NULL;
    } else {
        r->num = numerador;
        r->den = denominador;
    }

    /* Simplifica o racional antes de retorná-lo, conforme especificação para esta nova versão do programa: */
    simplifica_r(r);

    return r;
}

struct racional *sorteia_r (long int max){
    /* O valor de "min" da função "aleat" será sempre igual a "-max", conforme especificação: */
    int num = aleat(-max, max);
    int den = aleat(-max, max);

    struct racional *r = cria_r(num, den);

    return r;
}

void destroi_r (struct racional **r){
    r = NULL;
    free(r);
}

/* Retorna o numerador do racional r */
long int numerador_r (struct racional *r){
    return r->num;
}

/* Retorna o denominador do racional r */
long int denominador_r (struct racional *r){
    return r->den;
}

int valido_r (struct racional *r){
    /* Um racional é inválido se o denominador for nulo. */
    if (r->den == 0){
        return 0;
    } else {
        return 1;
    }
}

/* Retorna a soma (simplificada) dos racionais *r1 e *r2: */
struct racional *soma_r (struct racional *r1, struct racional *r2){
    int d = mmc(r1->den, r2->den);
    int n = ((d / r1->den) * r1->num) + ((d / r2->den) * r2->num);

    struct racional *r = malloc(sizeof(struct racional));

    if(r == NULL){
        return NULL;
    } else {
        r->num = n;
        r->den = d;
    }

    simplifica_r(r);
    return r;
}

/* Retorna a subtracao (simplificada) dos racionais *r1 e *r2: */
struct racional *subtrai_r (struct racional *r1, struct racional *r2){
    int d = mmc(r1->den, r2->den);
    int n = ((d / r1->den) * r1->num) - ((d / r2->den) * r2->num);

    struct racional *r = malloc(sizeof(struct racional));

    if(r == NULL){
        return NULL;
    } else {
        r->num = n;
        r->den = d;
    }

    simplifica_r(r);
    return r;
}

/* Retorna a multiplicacao (simplificada) dos racionais *r1 e *r2: */
struct racional *multiplica_r (struct racional *r1, struct racional *r2) {
    struct racional *r = malloc(sizeof(struct racional));

    if(r == NULL){
        return NULL;
    } else {
        r->num = r1->num * r2->num;
        r->den = r1->den * r2->den;
    }

    simplifica_r(r);
    return r;
}

/* Retorna a divisao (simplificada) dos racionais *r1 e *r2: */
struct racional *divide_r (struct racional *r1, struct racional *r2) {

    struct racional *r = malloc(sizeof(struct racional));

    if(r == NULL || r2->num == 0){
        return NULL;
    } else {
    
    }

    r->num = r1->num * r2->den;
    r->den = r1->den * r2->num;

    simplifica_r(r);
    
    return r;
}

/* Retorna -1 se r1 < r2; 0 se r1 == r2; 1 se r1 > r2 */
int compara_r (struct racional *r1, struct racional *r2){
    /* Calcula o MMC entre os denominadores: */
    int mmc_den = (r1->den * r2->den) / mdc(r1->den, r2->den);

    /* Normaliza os numeradores usando o MMC entre os denominadores, calculado acima: */
    int num1 = r1->num * (mmc_den / r1->den);
    int num2 = r2->num * (mmc_den / r2->den);

    /* Feita a normalização acima, agora é só comparar os numeradores: */
    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
}

void imprime_r (struct racional *r){
    /* O racional só poderá ser simplificado se não for inválido, ou seja, se o denominador for diferente de 0: */
    if (!valido_r(r)){
        printf("INVALIDO");
        return;
    } else {
        simplifica_r(r);
    }

    /* Casos em que pode-se omitir o denominador: */
    if ((r->num == 0) || (r->den == 1)){
        printf("%ld", r->num);
        return;
    }

    /* Se o numerador e o denominador tiverem o mesmo valor, deve imprimir somente 1: */
    if (r->num == r->den) {
        printf("1");
        return;
    }

    /* Caso geral, caso não tenha atendido as checagens acima: */
    printf("%ld/%ld", r->num, r->den);
    return;
}