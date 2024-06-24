#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

void elimina_invalidos(struct racional **v, int *n){
    int i = 0;

    /* Diferentemente de um laço do tipo "for",
    este laço do tipo "while" nem sempre irá incrementar a variável de controle.
    Isto ocorrerá apenas quando o elemento atual já tiver sido "tratado", ou seja,
    substituído por um racional válido do fim do vetor: */
    while (i < *n){
        if (denominador_r(v[i]) == 0){
            v[i] = v[*n - 1];
            *n = *n - 1;
        } else {
            i++;
        }
    }
}

void imprime_vetor(struct racional **v, int n){
    int i;
    for (i = 0; i < n; i++)
    {
        imprime_r(v[i]);
        printf(" ");
    }
    printf("\n");
}

/* Procedimento para trocar dois elementos,
que será usado para ordenar o vetor no particionamento do algoritmo QuickSort: */
void troca(struct racional **a, struct racional **b){
    struct racional *temp = *a;
    *a = *b;
    *b = temp;
}

/* Particionamento do QuickSort */
int particiona(struct racional **v, int low, int high){
    struct racional *pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compara_r(v[j], pivot) < 0) {
            i++;
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[i + 1], &v[high]);
    return i + 1;
}

/* Implementação do QuickSort */
void quicksort(struct racional **v, int low, int high){
    if (low < high) {
        int pivot = particiona(v, low, high);

        quicksort(v, low, pivot - 1);
        quicksort(v, pivot + 1, high);
    }
}

/* Função para somar todos os elementos do vetor: */
struct racional *soma_vetor(struct racional **v, int n) {
    struct racional *soma = cria_r(0, 1); /* Inicializando a soma como 0/1 */
    if (soma == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        soma = soma_r(soma, v[i]);
    }

    return soma;
}

int main (){
    int n, i;
    long int num_lido, den_lido;

    /* Inicializando a semente randômica: */
    srand(0);

    /* Lendo um número n tal que 0 < n < 100 conforme especificação: */
    do {
        scanf("%d", &n);
        if(n <= 0 || n >= 100){
            printf("O valor de n precisa estar entre 0 e 100. Tente novamente: ");
        }
    } while (n <= 0 || n >= 100);

    /* Declarando um vetor de ponteiros para racionais e alocando dinamicamente memória para o mesmo: */
    struct racional **v;
    v = malloc(n * sizeof(struct racional*));
    if (v == NULL){
        return 1;
    }

    /* Recebendo do usuário, via teclado, os valores para preencher o vetor: */
    for (i = 0; i < n; i++){
        scanf("%ld %ld", &num_lido, &den_lido);
        v[i] = cria_r(num_lido, den_lido);
    }

    imprime_vetor(v, n);

    elimina_invalidos(v, &n);

    imprime_vetor(v, n);

    /* Ordenando o vetor, através do algoritmo escolhido: */
    quicksort(v, 0, n-1);

    imprime_vetor(v, n);

    /* Calculando e imprimindo a soma de todos os elementos do vetor: */
    printf("a soma de todos os elementos eh: ");
    imprime_r(soma_vetor(v, n));

    /* Mudando de linha após a impressão da soma, conforme especificação: */
    printf("\n");

    /* Liberação de memória */
    for (i = 0; i < n; i++) {
        free(v[i]);
    }
    free(v);

    return 0;
}
