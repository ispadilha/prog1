#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* A diferenca desta implementação com relacao ao TP2
 * eh que os racionais devem alocados dinamicamente */

/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h.
 * Caso queira, voce pode definir neste arquivo funcoes
 * adicionais que serao internas a este arquivo.
 *
 * Por exemplo, as funções mdc e mmc devem ser
 * implementadas neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }

    return a;
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);

    return x;
}

/* Implemente aqui as funcoes cujos prototipos estao em racionais.h */

struct racional *cria_r (long int numerador, long int denominador){
    struct racional *r;

    r = malloc(sizeof(struct racional *));
    if (!r) 
        return NULL;

    r->num = numerador;
    r->den = denominador;

    if (valido_r(r)){
        simplifica_r(r);
    }
    return r;
}

int valido_r (struct racional *r){
    if (r->den == 0){
        return 0;
    } else {
        return 1;
    }
}

void imprime_r (struct racional *r){
    if (!valido_r(r)){
        printf("INVALIDO ");
        return;
    } else {
        simplifica_r(r);
    }

    if ((r->num == 0) || (r->den == 1)){
        printf("%ld ", r->num);
        return;
    }

    if (r->num == r->den) {
        printf("1 ");
        return;
    }

    printf("%ld/%ld ", r->num, r->den);
    return;
}

int simplifica_r (struct racional *r){
        /* Retorna 0 caso receba um racional inválido: */
    if (valido_r(r) == 0) return 0;
    
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