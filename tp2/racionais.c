#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* Retorna um número aleatório entre -max e max: */
int aleat (int min, int max){
    int tamanho = 2*max;
    int aux = (rand() % (tamanho + 1));
    int resultado = aux - max + min;

    return resultado;
}

/* Calcula o mdc pelo método de Euclides: */
int mdc (int a, int b){
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }

    return a;
}

/* Mínimo Multiplo Comum entre a e b, aproveitando a função MDC acima: */
int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);

    return x;
}

struct racional cria_r (int numerador, int denominador){
    struct racional r;
    r.num = numerador;
    r.den = denominador;

    if(denominador != 0){
        r.valido = 1;
    } else {
        /* Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando como inválido: */
        r.valido = 0;
    }

    return r;
}

/* Recebe um número racional no parâmetro e o simplifica: */
int simplifica_r (struct racional *r){
    /* Retorna 0 caso receba um racional inválido: */
    if (r->valido == 0) return 0;
    
    /* Simplifica o racional através da divisão de numerador e denominador pelo MDC entre os dois: */
    int mdc_r = mdc(r->num, r->den);
    r->num = ((r->num) / mdc_r);
    r->den = ((r->den) / mdc_r);

    /* Se numerador e denominador forem negativos, deverá resultar em positivo: */
    if((r->num < 0) && (r->den < 0)){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }

    /* Se apenas o denominador for negativo, o sinal deve migrar para o numerador: */
    if((r->den < 0)){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }

    /* Retorna 1 mediante operação bem sucedida: */
    return 1;
}

/* Retorna um número racional aleatório na forma simplificada: */
struct racional sorteia_r (int max){
    int den = (aleat(0, max));
    int num = (aleat(0, max));
    struct racional r = cria_r(num, den);
    simplifica_r(&r);

    return r;
}

/* Retorna o numerador de um racional: */
int numerador_r (struct racional r){
    return r.num;
}

/* Retorna o denominador de um racional: */
int denominador_r (struct racional r){
    return r.den;
}

/* Retorna 1 se o racional r é válido ou 0 caso contrário;
Um racional é inválido se o denominador for nulo: */
int valido_r (struct racional r){
    
    if (r.den == 0){
        return 0;
    } else {
        return 1;
    }
}

void imprime_r (struct racional r){
    if (!valido_r(r)){
        printf("INVALIDO ");
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

    /* Usando o MMC entre os denominadores, e com ele calculando os novos numeradores, para poder comparar os dois racionais */
    int mmc_den = mmc(r1.den, r2.den);
    int num1 = r1.num * (mmc_den / r1.den);
    int num2 = r2.num * (mmc_den / r2.den);

    /* Conforme o enunciado:
    Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2 */
    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
}


int soma_r (struct racional r1, struct racional r2, struct racional *r3) {
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }

    /* Uso "d" e "n" como variáveis para numerador e denominador, no escopo local;
    O denominador é o MMC entre as frações (números racionais), conforme a operação matemática correspondente */
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) + ((d/r2.den) * r2.num);

    r3->num = n;
    r3->den = d;

    /* Soma entre racionais válidos sempre será válida: */
    r3->valido = 1;

    /* Retorna 1 mediante operação bem sucedida: */
    return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }
   
    /* Bastante semelhante à função de soma, tomando o cuidado devido com o sinal */
    int d = mmc(r1.den, r2.den);
    int n = ((d/r1.den) * r1.num) - ((d/r2.den) * r2.num);
    
    r3->num = n;
    r3->den = d;

    /* Subtração entre racionais válidos sempre será válida: */
    r3->valido = 1;

    /* Retorna 1 mediante operação bem sucedida: */
    return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
    /* Retorna 0 caso receba um racional inválido. */
    if (!valido_r(r1) || !valido_r(r2)){
        return 0;
    }

    r3->num = (r1.num * r2.num);
    r3->den = (r1.den * r2.den);

    /* Multiplicação entre racionais válidos sempre será válida: */
    r3->valido = 1;

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

    /* Testa se o racional resultante também é válido: */
    r3->valido = valido_r(*r3);

    /* Retorna 1 mediante operação bem sucedida */
    return 1;
}