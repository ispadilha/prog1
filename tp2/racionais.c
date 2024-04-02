#include "racionais.h"

/* Retorna um número aleatório entre min e max, inclusive: */
int aleat (int min, int max){
    int tamanho = max - min;

    /* O operador módulo por (tamanho + 1) retornará um valor entre 0 e tamanho, inclusive: */
    int x = (rand() % (tamanho + 1));
    
    /* Somando (x + min) ao valor acima, o sorteio será entre min e max: */
    x = x + min;

    return x;
}

/* Calcula o MDC pelo método de Euclides, em sua versão recursiva: */
int mdc(int a, int b) {
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

/* Calcula o MMC, utilizando o MDC calculado anteriormente: */
int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);
    return x;
}

void simplifica_r(struct racional *r) {
    /* A função simplifica o racional recebido através da divisão de ambos, numerador e denominador, pelo MDC entre os dois;
    com sintaxe adaptada para o uso de ponteiros */
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

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/*
 * Implemente aqui as funcoes definidas no racionais.h.
*/
