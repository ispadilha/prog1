#include <stdio.h>
#include <stdlib.h>
#include "lef.h"

/* Cria um evento contendo os parâmetros informados */
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2){
    struct evento_t *novoEvento = (struct evento_t *) malloc(sizeof(struct evento_t));
    if (novoEvento == NULL){
        /* Retorna um ponteiro para NULL se falhar, conforme especificação */
        return NULL;
    }
        novoEvento->tempo = tempo;
        novoEvento->tipo = tipo;
        novoEvento->dado1 = dado1;
        novoEvento->dado2 = dado2;
    return novoEvento;
}

/* Destroi um evento e retorna NULL */
struct evento_t *destroi_evento (struct evento_t *e){
    free(e);
    return NULL;
}

/* Cria uma LEF vazia */
struct lef_t *cria_lef (){
    struct lef_t *novaLEF = (struct lef_t *) malloc(sizeof(struct lef_t));
    if (novaLEF == NULL){
        /* Retorna um ponteiro para NULL se falhar, conforme especificação */
        return NULL;
    }
    /* Por ser criada vazia, seu "primeiro" recebe NULL */
    novaLEF->primeiro = NULL;
    return novaLEF;
}

/* Destroi a LEF, liberando a memória ocupada por ela, inclusive os eventos.
Retorna NULL */
struct lef_t *destroi_lef (struct lef_t *l){
    struct nodo_lef_t *atual = l->primeiro;
    struct nodo_lef_t *prox;

    /* Enquanto um ponteiro iterador "atual" não for nulo,
    não chegou ao fim da lista */
    while (atual != NULL){
        /* Usa-se outro ponteiro "prox" para avançar nas iteracoes
        e poder destruir o "atual" a cada iteracao,
        sem perder ponteiros*/
        prox = atual->prox;
        destroi_evento(atual->evento);
        free(atual);
        atual = prox;
    }
    free(l);
    return NULL;
}

/* Insere o evento apontado na LEF na ordem de tempos crescentes.
Eventos com o mesmo tempo devem respeitar a politica FIFO.
Retorna 1 em caso de sucesso ou 0 caso contrario */
int insere_lef (struct lef_t *l, struct evento_t *e){
    struct nodo_lef_t *novoNodo = (struct nodo_lef_t *) malloc(sizeof(struct nodo_lef_t));
    if (novoNodo == NULL){
        return 0;
    }

    novoNodo->evento = e;
    /* Por ser politica FIFO, a insercao sera no final,
    por isso prox = NULL */
    novoNodo->prox = NULL;

    /* Será preciso percorrer a lista e para isso serão usados dois ponteiros,
    um deles guardando a posicao prévia do iterador "atual",
    para evitar perder ponteiros */
    struct nodo_lef_t *atual = l->primeiro;
    struct nodo_lef_t *prev = NULL;

    /* Percorrem e "incrementam" enquanto não chegar ao fim da lista,
    e o tempo do nodo atual, em cada iteracao, for menor que o tempo do evento
    do novo nodo, a ser inserido*/
    while (atual != NULL && atual->evento->tempo <= e->tempo){
        prev = atual;
        atual = atual->prox;
    }

    /* Se prev for NULL é porque não entrou no laço acima, portanto o novo nodo
    será o novo primeiro nodo da lista */
    if (prev == NULL){
        novoNodo->prox = l->primeiro;
        l->primeiro = novoNodo;
    } else {
        prev->prox = novoNodo;
        novoNodo->prox = atual;
    }

    return 1;
}

/* Retira o primeiro evento da LEF. Retorna ponteiro para o evento ou NULL se falhar */
struct evento_t *retira_lef (struct lef_t *l){
    if (l->primeiro == NULL){
        return NULL;
    }
    
    struct nodo_lef_t *n = l->primeiro;
    struct evento_t *e = n->evento;

    /* Atualiza o ponteiro "primeiro" da lista,
    para um nodo que será o "novo primeiro nodo",
    para poder liberar o antigo primeiro nodo */
    l->primeiro = n->prox;

    free(n);
    return e;
}

/* Informa se a LEF está vazia. Retorna 1 se vazia e 0 senao ou se falhar */
int vazia_lef (struct lef_t *l){
    if (l->primeiro == NULL){
        return 1;
    }
    return 0;
}

/* Imprime a LEF. Não faz parte do TAD, mas serve para depuração */
void imprime_lef (struct lef_t *l){
    struct nodo_lef_t *atual = l->primeiro;
    int i = 0;
    printf("LEF:\n");
    while (atual != NULL){
        printf("  tempo %d tipo %d d1 %d d2 %d\n", atual->evento->tempo, atual->evento->tipo,
               atual->evento->dado1, atual->evento->dado2);
        atual = atual->prox;
        i++;
    }
    printf("  Total %d eventos\n", i);
}
