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
    int x = (rand() % tamanho);
    /* A operação módulo retorna um resto de divisão,
    que estará dentro do intervalo correspondente ao tamanho */
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

    int i = 2;
    while((r.num % i != 0) && (r.den % i != 0)){
        r.num = (r.num / i);
        r.den = (r.den / i);
        i++;
        if ((i >= num) || (i >= den)){
            break;
        }
    }
    /* Utilizei uma variável "i" inicializada com o valor 2.
    Se o numerador e denominador, ambos, forem divisíveis pelo valor atual em "i", então essa divisão ocorre, para simplificação.
    Se "i" chegar ao valor de um dos dois, numerador ou denominador, é necessário romper a repetição. */

    if((r.num < 0) && (r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }
    /* Se ambos numerador e denominador forem negativos, devera retornar um positivo  */

    if((r.num > 0) && (r.den < 0)){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }
    /* Se o denominador for negativo, o sinal deve migrar para o numerador */

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

    return r;

    /* Cria uma struct do tipo racional, com os valores recebidos para numerador e  denominador.
    Se o valor do denominador for igual a zero, o campo "valido" da struct também recebe zero, assinalando como inválido. */
}

