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
    com sintaxe adaptada para o uso de ponteiros: */
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

/* Seguem as implementações das funções definidas no racionais.h: */

struct racional cria_r (int numerador, int denominador){
    struct racional r;
    r.num = numerador;
    r.den = denominador;

    /* struct racional consiste nos campos numerador, denominador, e "valido", portanto isso faz parte da criação do racional: */
    if(r.den == 0)
        r.valido = 0;
    else
        r.valido = 1;

    /* Simplifica o racional antes de retorná-lo, conforme especificação para esta nova versão do programa: */
    simplifica_r(&r);

    return r;
}

struct racional sorteia_r (int max){
    // Nesta nova versão do programa, o valor de "min" da função "aleat" será sempre igual a "-max", conforme a nova especificação:
    int num = aleat(-max, max);
    int den = aleat(-max, max);

    struct racional r = cria_r(num, den);

    return r;
}