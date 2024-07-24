#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* Cria e retorna uma nova fila */
struct fila *fila_cria () {
    struct fila *f = (struct fila *) malloc(sizeof(struct fila));
    if (f) {
        f->ini = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

/* Desaloca toda memoria da fila e faz fila receber NULL */
void fila_destroi (struct fila **f) {
    struct nodo *current = (*f)->ini;
    struct nodo *next;
    while (current != NULL) {
        next = current->prox;
        free(current);
        current = next;
    }
    free(*f);
    *f = NULL;
}

/* Insere dado na fila (politica FIFO). Retorna 1 em caso de sucesso e 0 em caso de falha */
int enqueue (struct fila *f, int dado) {
    struct nodo *n = (struct nodo *) malloc(sizeof(struct nodo));
    if (!n) return 0;
    n->chave = dado;
    n->prox = NULL;
    if (f->fim) f->fim->prox = n;
    f->fim = n;
    if (!f->ini) f->ini = n;
    f->tamanho++;
    return 1;
}

/* Remove dado da fila (politica FIFO) e retorna o elemento no parametro dado. Retorna 1 em caso de sucesso e 0 em caso de fila vazia */
int dequeue (struct fila *f, int *dado) {
    if (f->tamanho == 0) return 0;
    struct nodo *n = f->ini;
    *dado = n->chave;
    f->ini = n->prox;
    if (!f->ini) f->fim = NULL;
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
    return (f->tamanho == 0);
}
