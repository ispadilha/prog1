#include <stdio.h>
#include <stdlib.h>
#include "lef.h"

/* Cria um evento contendo os parâmetros informados */
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2) {
    struct evento_t *e = (struct evento_t *) malloc(sizeof(struct evento_t));
    if (e) {
        e->tempo = tempo;
        e->tipo = tipo;
        e->dado1 = dado1;
        e->dado2 = dado2;
    }
    return e;
}

/* Destroi um evento e retorna NULL */
struct evento_t *destroi_evento (struct evento_t *e) {
    free(e);
    return NULL;
}

/* Cria uma LEF vazia */
struct lef_t *cria_lef () {
    struct lef_t *l = (struct lef_t *) malloc(sizeof(struct lef_t));
    if (l) l->primeiro = NULL;
    return l;
}

/* Destroi a LEF, liberando a memória ocupada por ela, inclusive os eventos. Retorna NULL */
struct lef_t *destroi_lef (struct lef_t *l) {
    struct nodo_lef_t *current = l->primeiro;
    struct nodo_lef_t *next;
    while (current != NULL) {
        next = current->prox;
        destroi_evento(current->evento);
        free(current);
        current = next;
    }
    free(l);
    return NULL;
}

/* Insere o evento apontado na LEF na ordem de tempos crescentes. Eventos com o mesmo tempo devem respeitar a politica FIFO. Retorna 1 em caso de sucesso ou 0 caso contrario */
int insere_lef (struct lef_t *l, struct evento_t *e) {
    struct nodo_lef_t *novo = (struct nodo_lef_t *) malloc(sizeof(struct nodo_lef_t));
    if (!novo) return 0;
    novo->evento = e;
    novo->prox = NULL;

    struct nodo_lef_t *current = l->primeiro;
    struct nodo_lef_t *previous = NULL;

    while (current && current->evento->tempo <= e->tempo) {
        previous = current;
        current = current->prox;
    }

    if (previous == NULL) {
        novo->prox = l->primeiro;
        l->primeiro = novo;
    } else {
        previous->prox = novo;
        novo->prox = current;
    }

    return 1;
}

/* Retira o primeiro evento da LEF. Retorna ponteiro para o evento ou NULL se falhar */
struct evento_t *retira_lef (struct lef_t *l) {
    if (l->primeiro == NULL) return NULL;
    struct nodo_lef_t *n = l->primeiro;
    struct evento_t *e = n->evento;
    l->primeiro = n->prox;
    free(n);
    return e;
}

/* Informa se a LEF está vazia. Retorna 1 se vazia e 0 senao ou se falhar */
int vazia_lef (struct lef_t *l) {
    return (l->primeiro == NULL);
}

/* Imprime a LEF. Não faz parte do TAD, mas serve para depuração */
void imprime_lef (struct lef_t *l) {
    struct nodo_lef_t *current = l->primeiro;
    int count = 0;
    printf("LEF:\n");
    while (current) {
        printf("  tempo %d tipo %d d1 %d d2 %d\n", current->evento->tempo, current->evento->tipo,
               current->evento->dado1, current->evento->dado2);
        current = current->prox;
        count++;
    }
    printf("  Total %d eventos\n", count);
}
