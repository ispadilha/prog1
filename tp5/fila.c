#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* Cria e retorna uma nova fila */
struct fila *fila_cria () {
    struct fila *novaFila = (struct fila *) malloc(sizeof(struct fila));
    if (novaFila == NULL) {
        /* Retorna NULL em caso de erro de alocação, conforme especificação */
        return NULL;
    }
    novaFila->ini = NULL;
    novaFila->fim = NULL;
    novaFila->tamanho = 0;
    return novaFila;
}

/* Desaloca toda memoria da fila e faz fila receber NULL */
void fila_destroi (struct fila **filaADestruir) {
    struct nodo *atual = (*filaADestruir)->ini;
    struct nodo *prox;
    /* Enquanto não encontrar um ponteiro para nodo que seja NULL,
    a lista não acabou */
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(*filaADestruir);
    *filaADestruir = NULL;
}

/* Insere dado na fila (politica FIFO). Retorna 1 em caso de sucesso e 0 em caso de falha */
int enqueue (struct fila *f, int dado) {
    struct nodo *n = (struct nodo *) malloc(sizeof(struct nodo));
    
    if (n == NULL){
        return 0;
    }
    
    n->chave = dado;
    n->prox = NULL;
    
    /* Se já existem elementos, o atual último nodo é ajustado,
    para apontar para o novo último nodo (que é "n"). */
    if (f->fim != NULL){
        f->fim->prox = n;
    }

    f->fim = n;

    if (f->ini == NULL){
        f->ini = n;
    }

    f->tamanho++;
    return 1;
}

/* Remove dado da fila (politica FIFO) e retorna o elemento no parametro dado.
Retorna 1 em caso de sucesso e 0 em caso de fila vazia */
int dequeue (struct fila *f, int *dado) {
    if (f->tamanho == 0){
        return 0;
    }
    
    struct nodo *n = f->ini;

    /* Retorno no parametro, nao confundindo com retorno da funcao */
    *dado = n->chave;

    /* Atualizando o ponteiro para nodo "ini" (por ser politica FIFO) */
    f->ini = n->prox;

    /* Se só havia um nodo, ao ser retirado a lista fica vazia */
    if (f->ini == NULL){
        f->fim = NULL;
    }
    
    free(n);
    f->tamanho--;
    return 1;
}

/* Retorna o numero de elementos da fila, que pode ser 0 */
int fila_tamanho (struct fila *f) {
    return f->tamanho;
}

/* Retorna 1 se fila vazia, 0 em caso contrario */
int fila_vazia (struct fila *f) {
    if(f->tamanho == 0){
        return 1;
    }
    return 0;
}
