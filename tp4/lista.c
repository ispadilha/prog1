#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct lista *lista_cria (){
    /* Alocação dinâmica para a lista, que neste momento de sua criação,
    será apenas o nodo-cabeça, ... */
    struct lista *lista_a_criar = (struct lista *)malloc(sizeof(struct lista));
    if (lista_a_criar == NULL) return NULL;

    /* ...portanto não aponta para outros nós, e possui tamanho igual a 0: */
    lista_a_criar->ini = NULL;
    lista_a_criar->ptr = NULL;
    lista_a_criar->tamanho = 0;
    return lista_a_criar;
}

void lista_destroi (struct lista **lista){
    if (lista == NULL || *lista == NULL) return;
    /* Declara um ponteiro para nodo, para percorrer a lista: */
    struct nodo *iterando = (*lista)->ini;
    /* Percorre a lista usando outro ponteiro para nodo temporário,
    para liberar a memória de cada um deles, após avançar para o próximo: */
    while (iterando != NULL) {
        struct nodo *temp = iterando;
        iterando = iterando->prox;
        free(temp);
    }
    /* Por fim, libera a memória usada para o nodo cabeça, e aterra seu ponteiro: */
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    if (lista == NULL) return 0;
    /* Cria um ponteiro para um novo nodo e aloca memória para o mesmo: */
    struct nodo *nodo_a_inserir = (struct nodo *)malloc(sizeof(struct nodo));
    if (nodo_a_inserir == NULL) return 0;
    /* A chave deste novo nodo é aquela recebida por parâmetro: */
    nodo_a_inserir->chave = chave;
    /* O atual nodo inicial será o próximo do novo nodo inicial inserido: */
    nodo_a_inserir->prox = lista->ini;
    /* O nodo cabeça será atualizado, com este nodo inserido como o novo nodo inicial: */
    lista->ini = nodo_a_inserir;
    /* A lista pode então ter seu tamanho incrementado: */
    lista->tamanho++;
    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    if (lista == NULL) return 0;
    /* Cria um ponteiro para um novo nodo e aloca memória para o mesmo: */
    struct nodo *nodo_a_inserir = (struct nodo *)malloc(sizeof(struct nodo));
    if (nodo_a_inserir == NULL) return 0;
    /* A chave deste novo nodo é aquela recebida por parâmetro: */
    nodo_a_inserir->chave = chave;
    /* Como o novo nodo será inserido no fim, seu "próximo" será NULL: */
    nodo_a_inserir->prox = NULL;
    /* Se a lista estiver vazia, apenas insere como o nodo inicial: */
    if (lista->ini == NULL) {
        lista->ini = nodo_a_inserir;
    } else {
        struct nodo *iterando = lista->ini;
        /* Se a lista não estiver vazia, percorre-a para encontrar o último nodo: */
        while (iterando->prox != NULL) {
            iterando = iterando->prox;
        }
        /* Encontrado o nodo que é o último atualmente,
        atualiza seu "próximo" de NULL para o novo último nodo: */
        iterando->prox = nodo_a_inserir;
    }
    /* A lista pode então ter seu tamanho incrementado: */
    lista->tamanho++;
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    if (lista == NULL) return 0;
    /* Cria um ponteiro para um novo nodo e aloca memória para o mesmo: */
    struct nodo *nodo_a_inserir = (struct nodo *)malloc(sizeof(struct nodo));
    if (nodo_a_inserir == NULL) return 0;
    /* A chave deste novo nodo é aquela recebida por parâmetro: */
    nodo_a_inserir->chave = chave;
    /* Se a lista estiver vazia, ou se o valor da chave do nodo inicial for maior
    do que o valor a ser inserido, então este é inserido no início como novo nodo inicial: */
    if (lista->ini == NULL || lista->ini->chave > chave) {
        nodo_a_inserir->prox = lista->ini;
        lista->ini = nodo_a_inserir;
    } else {
        struct nodo *iterando = lista->ini;
        /* Percorre a lista enquanto o valor da chave for menor do que o valor a ser inserido,
        ou enquanto não chegar no último nodo, cujo "próximo" aponta para NULL */
        while (iterando->prox != NULL && iterando->prox->chave < chave) {
            iterando = iterando->prox;
        }
        nodo_a_inserir->prox = iterando->prox;
        iterando->prox = nodo_a_inserir;
    }
    /* A lista pode então ter seu tamanho incrementado: */
    lista->tamanho++;
    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if (lista == NULL || lista->ini == NULL) return 0;
    /* Cria um novo ponteiro para o nodo inicial: */
    struct nodo *nodo_a_remover = lista->ini;
    /* Guarda o elemento no parâmetro chave: */
    *chave = nodo_a_remover->chave;
    /* Altera a lista colocando o segundo nodo como o novo nodo inicial: */
    lista->ini = nodo_a_remover->prox;
    /* Libera a memória usada para o antigo nodo inicial: */
    free(nodo_a_remover);
    /* Após a remoção, pode-se diminuir o tamanho da lista: */
    lista->tamanho--;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if (lista == NULL || lista->ini == NULL) return 0;
    /* Cria um novo ponteiro para o nodo inicial, a fim de percorrer a lista: */
    struct nodo *iterando = lista->ini;
    /* Caso a lista tenha apenas um nodo, o inicial é também o final: */
    if (iterando->prox == NULL) {
        /* Guarda o elemento no parâmetro chave: */
        *chave = iterando->chave;
        /* Libera a memória usada para o nodo que, neste caso,
        nem precisou iterar: */
        free(iterando);
        /* Neste caso, a lista ficou vazia, portanto aterra o ponteiro do nodo cabeça: */
        lista->ini = NULL;
    } else {
        /* Caso a lista tenha mais de um nodo, é preciso outro ponteiro,
        para guardar o nodo anterior ao que está na iteração atual: */
        struct nodo *anterior;
        while (iterando->prox != NULL) {
            anterior = iterando;
            iterando = iterando->prox;
        }
        /* Ao encontrar um "próximo" que na verdade é NULL,
        isso significa que foi encontrado o último nodo.
        Então, guarda-se seu valor no parâmetro chave: */
        *chave = iterando->chave;
        /* E o antigo penúltimo nodo torna-se o novo último nodo,
        portanto seu "próximo" aponta para NULL: */
        anterior->prox = NULL;
        /* Libera a memória usada para o nodo que iterou percorrendo a lista: */
        free(iterando);
    }
    /* Após a remoção, pode-se diminuir o tamanho da lista: */
    lista->tamanho--;
    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave) {
    if (lista == NULL || lista->ini == NULL) return 0;
    
    /* Cria um novo ponteiro para o nodo inicial, a fim de percorrer a lista: */
    struct nodo *iterando = lista->ini;
    /* Outro ponteiro para nodo será necessário, para percorrer armazenando o nodo
    anterior ao que está iterando de forma principal: */
    struct nodo *anterior = NULL;
    
    /* Enquando não chegar ao fim da lista e não for encontrada a chave procurada,
    os ponteiros utilizados para percorrer a lista são "incrementados",
    isto é, avançam: */
    while (iterando != NULL && iterando->chave != chave) {
        anterior = iterando;
        iterando = iterando->prox;
    }
    
    /* Se a chave não foi encontrada na lista, a função retorna 0,
    conforme especificação: */
    if (iterando == NULL) return 0;
    
    if (anterior == NULL) {
        /* Se anterior continua sendo NULL, então não foi satisfeita condição
        para entrar no laço acima, e portanto a chave procurada
        foi encontrada no primeiro nodo da lista, o qual será então removido: */
        lista->ini = iterando->prox;
    } else {
        /* Senão, o laço acima ocorreu, e a chave procurada foi encontrada no meio
        ou no fim da lista, cujo nodo será então removido: */
        anterior->prox = iterando->prox;
    }
    
    /* Após remanejar os ponteiros, a memória referente ao nodo removido
    pode ser liberada: */
    free(iterando);
    /* Após a remoção, pode-se diminuir o tamanho da lista: */
    lista->tamanho--;
    return 1;
}


int lista_vazia (struct lista *lista){
    /* Caso o nodo cabeça aponte para NULL, significa que não há nenhum nodo,
    e portanto a lista está vazia: */
    if (lista->ini == NULL){
        return 1;
    } else {
        return 0;
    };
}

int lista_tamanho (struct lista *lista){
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    if (lista == NULL) return 0;
    /* Cria um novo ponteiro para nodo, inicialmente apontando para o início,
    a fim de percorrer a lista: */
    struct nodo *iterando = lista->ini;
    /* Enquanto não apontar para NULL, significa que não chegou ao fim da lista,
    então faz a verificação e incrementa a iteração: */
    while (iterando != NULL) {
        if (iterando->chave == chave) return 1;
        iterando = iterando->prox;
    }
    return 0;
}

void lista_inicia_iterador (struct lista *lista){
    if (lista == NULL) return;
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    if (lista == NULL || lista->ptr == NULL) return 0;
    /* "Retorna" o valor apontado no parâmetro, conforme especificação: */
    *chave = lista->ptr->chave;
    /* Avança para uma próxima iteração: */
    lista->ptr = lista->ptr->prox;
    /* Como passou pela verificação inicial deste escopo,
    então nesta iteração foi apontado um elemento válido,
    portanto pode-se retornar 1: */
    return 1;
}
