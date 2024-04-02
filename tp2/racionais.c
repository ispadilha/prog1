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
    /* Nesta nova versão do programa, o valor de "min" da função "aleat" será sempre igual a "-max", conforme a nova especificação: */
    int num = aleat(-max, max);
    int den = aleat(-max, max);

    struct racional r = cria_r(num, den);

    return r;
}

/* Retorna o numerador do racional r */
int numerador_r (struct racional r){
    return r.num;
}

/* Retorna o denominador do racional r */
int denominador_r (struct racional r){
    return r.den;
}

int valido_r (struct racional r){
    /* Conforme especificação, esta função se limita a testar o campo "valido" da struct,
    o qual deve ter sido inicializado previamente nas demais funções: */
    if (r.valido == 0){
        return 0;
    } else {
        return 1;
    }
}

/* Retorna a soma (simplificada) dos racionais r1 e r2 no parâmetro *r3, bem como inicializa o campo "valido" deste: */
void soma_r (struct racional r1, struct racional r2, struct racional *r3){
    int d = mmc(r1.den, r2.den);
    int n = ((d / r1.den) * r1.num) + ((d / r2.den) * r2.num);

    r3->num = n;
    r3->den = d;

    r3->valido = valido_r(*r3);

    simplifica_r(r3);
}

/* Retorna a subtração (simplificada) dos racionais r1 e r2 no parâmetro *r3, bem como inicializa o campo "valido" deste: */
void subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    int d = mmc(r1.den, r2.den);
    int n = ((d / r1.den) * r1.num) - ((d / r2.den) * r2.num);

    r3->num = n;
    r3->den = d;

    r3->valido = valido_r(*r3);

    simplifica_r(r3);
}

/* Retorna a multiplicação dos racionais r1 e r2 no parâmetro *r3, bem como inicializa o campo "valido" deste: */
void multiplica_r(struct racional r1, struct racional r2, struct racional *r3) {
    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;

    r3->valido = valido_r(*r3);

    simplifica_r(r3);
}

/* Retorna a divisão dos racionais r1 e r2 no parâmetro *r3; a função em si retorna 1 se r3 for válido ou 0 caso contrário. */
int divide_r(struct racional r1, struct racional r2, struct racional *r3) {
    if (r2.num == 0) {
        r3->valido = 0;
        return 0;
    } else {
        r3->num = r1.num * r2.den;
        r3->den = r1.den * r2.num;
        
        r3->valido = valido_r(*r3);

        simplifica_r(r3);
        
        return 1;
    }
}

/* Retorna -1 se r1 < r2; 0 se r1 == r2; 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){
    /* Calcula o MMC entre os denominadores: */
    int mmc_den = (r1.den * r2.den) / mdc(r1.den, r2.den);

    /* Normaliza os numeradores usando o MMC entre os denominadores, calculado acima: */
    int num1 = r1.num * (mmc_den / r1.den);
    int num2 = r2.num * (mmc_den / r2.den);

    /* Feita a normalização acima, agora é só comparar os numeradores: */
    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
}