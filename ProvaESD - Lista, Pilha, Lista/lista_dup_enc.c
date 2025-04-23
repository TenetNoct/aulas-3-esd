#include "lista_dup_enc.h"
#include <stdlib.h>
#include <stdio.h>

// Função auxiliar para criar um novo nó
static NoListaDupEnc* criar_no_dup(TipoElementoListaDupEnc elemento) {
    NoListaDupEnc* novo_no = (NoListaDupEnc*)malloc(sizeof(NoListaDupEnc));
    if (!novo_no) {
        perror("Erro ao alocar memória para novo nó duplo");
        return NULL;
    }
    novo_no->dado = elemento;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;
    return novo_no;
}

// Função auxiliar para obter o nó em uma posição específica (otimizada)
static NoListaDupEnc* obter_no_posicao(const ListaDupEnc* l, int posicao) {
    if (posicao < 0 || posicao >= l->tamanho) {
        return NULL; // Posição inválida
    }

    NoListaDupEnc* atual;
    // Otimização: começa a busca do lado mais próximo (início ou fim)
    if (posicao < l->tamanho / 2) {
        atual = l->inicio;
        for (int i = 0; i < posicao; i++) {
            atual = atual->proximo;
        }
    } else {
        atual = l->fim;
        for (int i = l->tamanho - 1; i > posicao; i--) {
            atual = atual->anterior;
        }
    }
    return atual;
}

// --- Implementação das Funções ---

ListaDupEnc* lista_dup_enc_criar() {
    ListaDupEnc* l = (ListaDupEnc*)malloc(sizeof(ListaDupEnc));
    if (!l) {
        perror("Erro ao alocar memória para a lista dupla");
        return NULL;
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void lista_dup_enc_destruir(ListaDupEnc** l) {
    if (!l || !*l) return;

    NoListaDupEnc* atual = (*l)->inicio;
    NoListaDupEnc* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    free(*l);
    *l = NULL;
}

bool lista_dup_enc_vazia(const ListaDupEnc* l) {
    if (!l) return true;
    return l->tamanho == 0; // Ou l->inicio == NULL
}

bool lista_dup_enc_inserir_inicio(ListaDupEnc* l, TipoElementoListaDupEnc elemento) {
    if (!l) return false;
    NoListaDupEnc* novo_no = criar_no_dup(elemento);
    if (!novo_no) return false;

    if (lista_dup_enc_vazia(l)) {
        l->inicio = novo_no;
        l->fim = novo_no;
    } else {
        novo_no->proximo = l->inicio;
        l->inicio->anterior = novo_no;
        l->inicio = novo_no;
    }
    l->tamanho++;
    return true;
}

bool lista_dup_enc_inserir_fim(ListaDupEnc* l, TipoElementoListaDupEnc elemento) {
    if (!l) return false;
    NoListaDupEnc* novo_no = criar_no_dup(elemento);
    if (!novo_no) return false;

    if (lista_dup_enc_vazia(l)) {
        l->inicio = novo_no;
        l->fim = novo_no;
    } else {
        novo_no->anterior = l->fim;
        l->fim->proximo = novo_no;
        l->fim = novo_no;
    }
    l->tamanho++;
    return true;
}

bool lista_dup_enc_inserir_posicao(ListaDupEnc* l, TipoElementoListaDupEnc elemento, int posicao) {
    if (!l || posicao < 0 || posicao > l->tamanho) {
        fprintf(stderr, "Erro: Posição de inserção inválida (%d). Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    if (posicao == 0) {
        return lista_dup_enc_inserir_inicio(l, elemento);
    }
    if (posicao == l->tamanho) {
        return lista_dup_enc_inserir_fim(l, elemento);
    }

    // Inserir no meio
    NoListaDupEnc* novo_no = criar_no_dup(elemento);
    if (!novo_no) return false;

    NoListaDupEnc* no_atual_na_posicao = obter_no_posicao(l, posicao);
    if (!no_atual_na_posicao) return false; // Segurança, não deve acontecer

    NoListaDupEnc* no_anterior = no_atual_na_posicao->anterior;

    novo_no->proximo = no_atual_na_posicao;
    novo_no->anterior = no_anterior;

    no_anterior->proximo = novo_no;
    no_atual_na_posicao->anterior = novo_no;

    l->tamanho++;
    return true;
}

bool lista_dup_enc_remover_inicio(ListaDupEnc* l, TipoElementoListaDupEnc* removido) {
    if (!l || lista_dup_enc_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do início.\n");
        return false;
    }

    NoListaDupEnc* no_removido = l->inicio;
    if (removido) {
        *removido = no_removido->dado;
    }

    l->inicio = no_removido->proximo;
    if (l->inicio != NULL) {
        l->inicio->anterior = NULL; // O novo início não tem anterior
    } else {
        l->fim = NULL; // A lista ficou vazia
    }

    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_remover_fim(ListaDupEnc* l, TipoElementoListaDupEnc* removido) {
    if (!l || lista_dup_enc_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do fim.\n");
        return false;
    }

    NoListaDupEnc* no_removido = l->fim;
    if (removido) {
        *removido = no_removido->dado;
    }

    l->fim = no_removido->anterior;
    if (l->fim != NULL) {
        l->fim->proximo = NULL; // O novo fim não tem próximo
    } else {
        l->inicio = NULL; // A lista ficou vazia
    }

    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_remover_posicao(ListaDupEnc* l, int posicao, TipoElementoListaDupEnc* removido) {
    if (!l || lista_dup_enc_vazia(l) || posicao < 0 || posicao >= l->tamanho) {
        fprintf(stderr, "Erro: Posição de remoção inválida (%d) ou lista vazia. Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    if (posicao == 0) {
        return lista_dup_enc_remover_inicio(l, removido);
    }
    if (posicao == l->tamanho - 1) {
        return lista_dup_enc_remover_fim(l, removido);
    }

    // Remover do meio
    NoListaDupEnc* no_removido = obter_no_posicao(l, posicao);
    if (!no_removido) return false; // Segurança

    if (removido) {
        *removido = no_removido->dado;
    }

    NoListaDupEnc* no_anterior = no_removido->anterior;
    NoListaDupEnc* no_proximo = no_removido->proximo;

    no_anterior->proximo = no_proximo;
    no_proximo->anterior = no_anterior;

    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_buscar(const ListaDupEnc* l, TipoElementoListaDupEnc elemento, int* indice) {
    if (!l) return false;

    NoListaDupEnc* atual = l->inicio;
    int i = 0;
    while (atual != NULL) {
        if (atual->dado == elemento) {
            if (indice) {
                *indice = i;
            }
            return true; // Encontrado
        }
        atual = atual->proximo;
        i++;
    }
    return false; // Não encontrado
}

bool lista_dup_enc_obter_elemento(const ListaDupEnc* l, int posicao, TipoElementoListaDupEnc* elemento) {
    NoListaDupEnc* no = obter_no_posicao(l, posicao);
    if (!no) {
         fprintf(stderr, "Erro: Posição inválida (%d) para obter elemento. Tamanho: %d\n", posicao, l ? l->tamanho : -1);
        return false;
    }

    if (elemento) {
        *elemento = no->dado;
    }
    return true;
}

int lista_dup_enc_tamanho(const ListaDupEnc* l) {
    if (!l) return 0;
    return l->tamanho;
}

void lista_dup_enc_imprimir_frente(const ListaDupEnc* l) {
    if (!l) {
        printf("Lista dupla inválida.\n");
        return;
    }
    if (lista_dup_enc_vazia(l)) {
        printf("Lista (frente): [] (vazia)\n");
        return;
    }
    printf("Lista (frente): [ ");
    NoListaDupEnc* atual = l->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("] (Tamanho: %d)\n", l->tamanho);
}

void lista_dup_enc_imprimir_tras(const ListaDupEnc* l) {
    if (!l) {
        printf("Lista dupla inválida.\n");
        return;
    }
    if (lista_dup_enc_vazia(l)) {
        printf("Lista (trás): [] (vazia)\n");
        return;
    }
    printf("Lista (trás): [ ");
    NoListaDupEnc* atual = l->fim;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }
    printf("] (Tamanho: %d)\n", l->tamanho);
}