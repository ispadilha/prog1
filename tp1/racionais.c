#include "racionais.h"
/* acrescente demais includes que voce queira ou precise */
#include "time.h"

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/

int aleat (int min, int max){
    int tamanho = max - min;
    int x = (rand() % (tamanho + 1));
    x = x + min;

    /* A operação módulo retorna um resto de divisão,
    que estará dentro do intervalo correspondente a tamanho - 1.
    Para corrigir isto, calculo o módulo por tamanho + 1.
    Isto sorteia um número entre 0 e tamanho. Por isso, somo x + min.
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
    Quando o resto for zero, a repetição termina. E o resultado, ou seja, o MDC estará armazenado em "a". */

    return a;
}

int mmc (int a, int b){
    int x = (a*b)/mdc(a,b);

    /* É possível utilizar a função anterior do MDC */

    return x;
}

struct racional simplifica_r (struct racional r){
    if (r.valido == 0) return r;

    /* Se o racional "r" fornecido for inválido (com denominador zero), a função não tem o que fazer,
    além de devolver o mesmo racional sem operar nada */

    int mdc_r = mdc(r.num, r.den);
    r.num = (r.num / mdc_r);
    r.den = (r.den / mdc_r);

    /* Aproveitei a função criada anteriormente, para encontrar o MDC entre o numerador e o denominador.
    A função simplifica o racional recebido através da divisão de ambos, numerador e denominador, pelo MDC entre os dois. */

    if((r.num < 0) && (r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    /* Se ambos, numerador e denominador, forem negativos, deverá retornar um positivo  */

    if((r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }

    /* Se apenas o denominador for negativo, o sinal deve migrar para o numerador */

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

    /* Cria uma struct do tipo racional, com os valores recebidos para numerador e  denominador.
    Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando como inválido. */

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

/* void imprime_r (struct racional r); */
/* IMPLEMENTAR */

int valido_r (struct racional r){

    /* Um racional eh invalido se o denominador for nulo */
    
    if (r.den == 0){
        return 0;
    } else {
        return 1;
    }
}