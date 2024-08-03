#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"
#include "lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 6)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

typedef struct {
    int id;
    struct conjunto *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
} heroi_t;

typedef struct {
    int id;
    int lotacao;
    struct conjunto *presentes;
    struct fila *espera;
    int x, y;
} base_t;

typedef struct {
    int id;
    struct conjunto *habilidades;
    int x, y;
    int tentativas;
    int cumprida;
} missao_t;

typedef struct {
    int nHerois;
    heroi_t herois[N_HEROIS];
    int nBases;
    base_t bases[N_BASES];
    int nMissoes;
    missao_t missoes[N_MISSOES];
    int nHabilidades;
    int tamanhoMundo;
    int relogio;
} mundo_t;

mundo_t mundo;
struct lef_t *lef;

/* Função auxiliar */
int distancia(int x1, int y1, int x2, int y2) {
    /* todo pensar numa forma melhor de medir distância (pitágoras?): */
    return abs(x2 - x1) + abs(y2 - y1);
}

/* Inicialização das entidades */
void inicializa_herois() {
    int i, j;
    for (i = 0; i < N_HEROIS; i++) {
        mundo.herois[i].id = i;
        mundo.herois[i].habilidades = cria_cjt(N_HABILIDADES);
        mundo.herois[i].paciencia = rand() % 101;
        /* Velocidade de 50 a 5000, conforme especificação: */
        mundo.herois[i].velocidade = 50 + rand() % 4951;
        mundo.herois[i].experiencia = 0;
        mundo.herois[i].base = rand() % N_BASES;

        int numHabilidades = 1 + rand() % 3;
        for (j = 0; j < numHabilidades; j++) {
            int habilidade = rand() % N_HABILIDADES;
            /* Enquanto uma habilidade sorteada for repetida (já pertencer ao conjunto), sorteia novamente: */
            while (pertence_cjt(mundo.herois[i].habilidades, habilidade)) {
                habilidade = rand() % N_HABILIDADES;
            }
            insere_cjt(mundo.herois[i].habilidades, habilidade);
        }
    }
}

void inicializa_bases() {
    int i;
    for (i = 0; i < N_BASES; i++) {
        mundo.bases[i].id = i;
        mundo.bases[i].x = rand() % N_TAMANHO_MUNDO;
        mundo.bases[i].y = rand() % N_TAMANHO_MUNDO;
        /* Lotação de 3 a 10, conforme especificação: */
        mundo.bases[i].lotacao = 3 + rand() % 8;
        mundo.bases[i].presentes = cria_cjt(mundo.bases[i].lotacao);
        mundo.bases[i].espera = fila_cria();
    }
}

void inicializa_missoes() {
    int i, j;
    for (i = 0; i < N_MISSOES; i++) {
        mundo.missoes[i].id = i;
        mundo.missoes[i].x = rand() % N_TAMANHO_MUNDO;
        mundo.missoes[i].y = rand() % N_TAMANHO_MUNDO;
        mundo.missoes[i].habilidades = cria_cjt(N_HABILIDADES);
        mundo.missoes[i].tentativas = 0;
        mundo.missoes[i].cumprida = 0;

        /* Habilidades requeridas para missão são de 6 a 10, conforme especificação: */
        int numHabilidades = 6 + rand() % 5;
        for (j = 0; j < numHabilidades; j++) {
            int habilidade = rand() % N_HABILIDADES;
            /* Enquanto uma habilidade sorteada for repetida (já pertencer ao conjunto), sorteia novamente: */
            while (pertence_cjt(mundo.missoes[i].habilidades, habilidade)) {
                habilidade = rand() % N_HABILIDADES;
            }
            insere_cjt(mundo.missoes[i].habilidades, habilidade);
        }
    }
}

void inicializa_mundo() {

    /* Estado inicial: */
    mundo.nHerois = N_HEROIS;
    mundo.nBases = N_BASES;
    mundo.nMissoes = N_MISSOES;
    mundo.nHabilidades = N_HABILIDADES;
    mundo.tamanhoMundo = N_TAMANHO_MUNDO;
    mundo.relogio = T_INICIO;

    inicializa_herois();
    inicializa_bases();
    inicializa_missoes();

    /* Eventos iniciais: */
    lef = cria_lef();

    int i;

    /* Cada herói chegará em uma base aleatória em algum momento dos três primeiros dias de simulação:  */
    /* 4320 = 60*24*3 = 3 dias */
    for (i = 0; i < N_HEROIS; i++) {
        int tempo = rand() % 4321;
        struct evento_t *evento_chega = cria_evento(tempo, 1, i, mundo.herois[i].base);
        insere_lef(lef, evento_chega);
    }

    /* Cada missão deve ser agendada para ocorrer em algum momento da simulação: */
    for (i = 0; i < N_MISSOES; i++) {
        int tempo = rand() % (T_FIM_DO_MUNDO + 1);
        struct evento_t *evento_missao = cria_evento(tempo, 2, i, 0);
        insere_lef(lef, evento_missao);
    }

    /* O evento FIM deve ser agendado para o instante final da simulação:  */
    struct evento_t *evento_fim = cria_evento(T_FIM_DO_MUNDO, 3, 0, 0);
    insere_lef(lef, evento_fim);
}

void processa_evento_chega(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int b = ev->dado2;
    if (h >= mundo.nHerois || b >= mundo.nBases) return;
    heroi_t *heroi = &mundo.herois[h];
    base_t *base = &mundo.bases[b];

    /* atualiza base de H: */
    mundo.herois[h].base = b;

    int espera;
    /* se há vagas em B e a fila de espera em B está vazia: */
    if (base->presentes->card < base->lotacao && fila_vazia(base->espera)) {
        espera = 1;
    } else {
        espera = heroi->paciencia > 10 * fila_tamanho(base->espera);
    }

    if (espera) {
        printf("%6d: CHEGA   HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, h, b, base->presentes->card, base->lotacao);
        struct evento_t *evento_espera = cria_evento(tempo, 4, h, b);
        insere_lef(lef, evento_espera);
    } else {
        printf("%6d: CHEGA   HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, h, b, base->presentes->card, base->lotacao);
        struct evento_t *evento_desiste = cria_evento(tempo, 5, h, b);
        insere_lef(lef, evento_desiste);
    }
}

void processa_evento_espera(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int b = ev->dado2;
    if (h >= mundo.nHerois || b >= mundo.nBases) return;
    base_t *base = &mundo.bases[b];

    /* adiciona H ao fim da fila de espera de B: */
    enqueue(base->espera, h);
    printf("%6d: ESPERA  HEROI %2d BASE %d (%2d)\n", tempo, h, b, fila_tamanho(base->espera));

    struct evento_t *evento_avisa = cria_evento(tempo, 6, b, 0);
    insere_lef(lef, evento_avisa);
}

void processa_evento_desiste(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int b = ev->dado2;
    if (h >= mundo.nHerois || b >= mundo.nBases) return;

    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, h, b);

    /* escolhe uma base destino D aleatória: */
    int d = rand() % N_BASES;
    struct evento_t *evento_viaja = cria_evento(tempo, 7, h, d);
    insere_lef(lef, evento_viaja);
}

void processa_evento_avisa(struct evento_t *ev) {
    int tempo = ev->tempo;
    int b = ev->dado1;
    if (b >= mundo.nBases)
        return;
    base_t *base = &mundo.bases[b];

    /* Imprime a mensagem de saída com os dados da fila: */
    printf("%6d: AVISA   PORTEIRO BASE %d (%2d/%2d) FILA [", tempo, b, base->presentes->card, base->lotacao);
    struct nodo *atual = base->espera->ini;
    while (atual != NULL) {
        printf(" %2d", atual->chave);
        atual = atual->prox;
    }
    printf(" ]\n");

    /* enquanto houver vaga em B e houver heróis esperando na fila: */
    while (base->presentes->card < base->lotacao && !fila_vazia(base->espera)) {
        int h;
        /* retira primeiro herói (H') da fila de B: */
        dequeue(base->espera, &h);
        /* adiciona H' ao conjunto de heróis presentes em B: */
        insere_cjt(base->presentes, h);
        printf("%6d: AVISA   PORTEIRO BASE %d ADMITE %2d\n", tempo, b, h);
        struct evento_t *evento_entra = cria_evento(tempo, 8, h, b);
        insere_lef(lef, evento_entra);
    }
}

void processa_evento_entra(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int b = ev->dado2;
    if (h >= mundo.nHerois || b >= mundo.nBases) return;
    heroi_t *heroi = &mundo.herois[h];
    base_t *base = &mundo.bases[b];

    /* calcula TPB = tempo de permanência na base:
    TPB = 15 + paciência de H * aleatório [1...20] */
    int tpb = 15 + heroi->paciencia * (rand() % 20 + 1);

    printf("%6d: ENTRA   HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h, b, base->presentes->card, base->lotacao, tempo + tpb);

    struct evento_t *evento_sai = cria_evento(tempo + tpb, 9, h, b);
    insere_lef(lef, evento_sai);
}

void processa_evento_sai(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int b = ev->dado2;
    if (h >= mundo.nHerois || b >= mundo.nBases) return;
    base_t *base = &mundo.bases[b];

    /* retira H do conjunto de heróis presentes em B: */
    retira_cjt(base->presentes, h);

    printf("%6d: SAI     HEROI %2d BASE %d (%2d/%2d)\n", tempo, h, b, base->presentes->card, base->lotacao);

    /* escolhe uma base destino D aleatória: */
    int d = rand() % N_BASES;
    struct evento_t *evento_viaja = cria_evento(tempo, 7, h, d);
    insere_lef(lef, evento_viaja);
    struct evento_t *evento_avisa = cria_evento(tempo, 6, b, 0);
    insere_lef(lef, evento_avisa);
}

void processa_evento_viaja(struct evento_t *ev) {
    int tempo = ev->tempo;
    int h = ev->dado1;
    int d = ev->dado2;
    if (h >= mundo.nHerois || d >= mundo.nBases) return;
    heroi_t *heroi = &mundo.herois[h];
    base_t *base_atual = &mundo.bases[heroi->base];
    base_t *base_destino = &mundo.bases[d];

    /* calcula distância e duração da viagem: */
    int dist = distancia(base_atual->x, base_atual->y, base_destino->x, base_destino->y);
    int duracao = dist / heroi->velocidade;
    printf("%6d: VIAJA   HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, h, base_atual->id, d, dist, heroi->velocidade, tempo + duracao);

    struct evento_t *evento_chega = cria_evento(tempo + duracao, 1, h, d);
    insere_lef(lef, evento_chega);
}

void processa_evento_missao(struct evento_t *ev) {
    int tempo = ev->tempo;
    int m = ev->dado1;
    if (m >= mundo.nMissoes) return;
    missao_t *missao = &mundo.missoes[m];

    missao->tentativas++;
    printf("%6d: MISSAO  %d TENT %d HAB REQ: [", tempo, m, missao->tentativas);
    int i;
    for (i = 0; i < missao->habilidades->card; i++) {
        int hab;
        incrementa_iterador_cjt(missao->habilidades, &hab);
        printf(" %d", hab);
    }
    printf(" ]\n");

    base_t *base_mais_proxima = NULL;
    int menor_distancia = N_TAMANHO_MUNDO * 2;

    /* calcula a distância de cada base ao local da missão M, e encontra a base mais próxima: */
    for (i = 0; i < N_BASES; i++) {
        base_t *base = &mundo.bases[i];
        int dist = distancia(base->x, base->y, missao->x, missao->y);
        if (dist < menor_distancia) {
            menor_distancia = dist;
            base_mais_proxima = base;
        }
    }

    if (base_mais_proxima != NULL) {
        struct conjunto *habilidades_unidas = cria_cjt(N_HABILIDADES);
        int heroi_id;
        inicia_iterador_cjt(base_mais_proxima->presentes);
        printf("%6d: MISSAO  %d BASE %d DIST %d HEROIS [", tempo, m, base_mais_proxima->id, menor_distancia);
        while (incrementa_iterador_cjt(base_mais_proxima->presentes, &heroi_id)) {
            heroi_t *heroi = &mundo.herois[heroi_id];
            printf(" %d", heroi_id);
            int hab;
            inicia_iterador_cjt(heroi->habilidades);
            while (incrementa_iterador_cjt(heroi->habilidades, &hab)) {
                insere_cjt(habilidades_unidas, hab);
            }
        }
        printf(" ]\n");

        /* Inicializa uma flag para verificar se as habilidades unidas, dos heróis presentes na base,
        formam um conjunto compatível com as habilidades requeridas pela missão: */
        int pode_cumprir = 1;
        for (i = 0; i < missao->habilidades->card; i++) {
            int hab;
            incrementa_iterador_cjt(missao->habilidades, &hab);
            if (!pertence_cjt(habilidades_unidas, hab)) {
                pode_cumprir = 0;
                break;
            }
        }

        if (pode_cumprir) {
            printf("%6d: MISSAO  %d CUMPRIDA BASE %d\n", tempo, m, base_mais_proxima->id);
            missao->cumprida = 1;
            inicia_iterador_cjt(base_mais_proxima->presentes);
            while (incrementa_iterador_cjt(base_mais_proxima->presentes, &heroi_id)) {
                mundo.herois[heroi_id].experiencia++;
            }
        } else {
            printf("%6d: MISSAO  %d IMPOSSIVEL\n", tempo, m);
            struct evento_t *evento_missao = cria_evento(tempo + 24 * 60, 2, m, 0);
            insere_lef(lef, evento_missao);
        }

        destroi_cjt(habilidades_unidas);
    } else {
        printf("%6d: MISSAO  %d IMPOSSIVEL\n", tempo, m);
        struct evento_t *evento_missao = cria_evento(tempo + 24 * 60, 2, m, 0);
        insere_lef(lef, evento_missao);
    }
}

void processa_evento_fim(struct evento_t *ev) {
    int tempo = ev->tempo;
    printf("%6d: FIM\n", tempo);
    int i;

    /* apresenta as experiências dos heróis: */
    for (i = 0; i < N_HEROIS; i++) {
        heroi_t *heroi = &mundo.herois[i];
        printf("HEROI %2d PAC %3d VEL %4d EXP %4d HABS [", heroi->id, heroi->paciencia, heroi->velocidade, heroi->experiencia);
        int hab;
        inicia_iterador_cjt(heroi->habilidades);
        while (incrementa_iterador_cjt(heroi->habilidades, &hab)) {
            printf(" %d", hab);
        }
        printf(" ]\n");
    }

    int missoes_cumpridas = 0;
    int total_tentativas = 0;
    int min_tentativas = N_MISSOES;
    int max_tentativas = 0;
    for (i = 0; i < N_MISSOES; i++) {
        if (mundo.missoes[i].cumprida) {
            missoes_cumpridas++;
        }
        total_tentativas += mundo.missoes[i].tentativas;
        if (mundo.missoes[i].tentativas < min_tentativas) {
            min_tentativas = mundo.missoes[i].tentativas;
        }
        if (mundo.missoes[i].tentativas > max_tentativas) {
            max_tentativas = mundo.missoes[i].tentativas;
        }
    }

    /* apresenta as estatísticas das missões: */
    float media_tentativas = (float)total_tentativas / N_MISSOES;
    printf("MISSOES CUMPRIDAS: %d/%d (%.2f%%)\n", missoes_cumpridas, N_MISSOES, (float)missoes_cumpridas / N_MISSOES * 100);
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.2f\n", min_tentativas, max_tentativas, media_tentativas);
}

void processa_evento(struct evento_t *ev) {
    switch (ev->tipo) {
        case 1: /* Evento CHEGA */
            processa_evento_chega(ev);
            break;
        case 2: /* Evento MISSAO */
            processa_evento_missao(ev);
            break;
        case 3: /* Evento FIM */
            processa_evento_fim(ev);
            break;
        case 4: /* Evento ESPERA */
            processa_evento_espera(ev);
            break;
        case 5: /* Evento DESISTE */
            processa_evento_desiste(ev);
            break;
        case 6: /* Evento AVISA */
            processa_evento_avisa(ev);
            break;
        case 8: /* Evento ENTRA */
            processa_evento_entra(ev);
            break;
        case 9: /* Evento SAI */
            processa_evento_sai(ev);
            break;
        case 7: /* Evento VIAJA */
            processa_evento_viaja(ev);
            break;
        default:
            printf("Evento desconhecido: %d\n", ev->tipo);
    }
}

void executa_simulacao() {
    while (mundo.relogio < T_FIM_DO_MUNDO) {
        struct evento_t *ev = retira_lef(lef);
        if (ev == NULL) break;
        mundo.relogio = ev->tempo;
        processa_evento(ev);
        destroi_evento(ev);
    }
}

/* Libera a memória usada nos diferentes conjuntos de habilidades, de heróis
presentes em cada base, e suas filas de espera: */
void destroi_mundo() {
    int i;

    for (i = 0; i < N_HEROIS; i++)
    {
        destroi_cjt(mundo.herois[i].habilidades);
    }
    for (i = 0; i < N_BASES; i++) {
        destroi_cjt(mundo.bases[i].presentes);
        fila_destroi(&mundo.bases[i].espera);
    }
    for (i = 0; i < N_MISSOES; i++) {
        destroi_cjt(mundo.missoes[i].habilidades);
    }
    destroi_lef(lef);
}

int main() {
    srand(0); /* Use zero, não faça com time(0) */

    inicializa_mundo();
    executa_simulacao();
    destroi_mundo();

    return 0;
}
