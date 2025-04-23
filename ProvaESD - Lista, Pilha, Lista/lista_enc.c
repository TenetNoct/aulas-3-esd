#include "lista_enc.h"
#include <stdlib.h>
#include <stdio.h>

// Função auxiliar para criar um novo nó
static NoListaEnc* criar_no(TipoElementoListaEnc elemento) {
    NoListaEnc* novo_no = (NoListaEnc*)malloc(sizeof(NoListaEnc));
    if (!novo_no) {
        perror("Erro ao alocar memória para novo nó");
        return NULL;
    }
    novo_no->dado = elemento;
    novo_no->proximo = NULL;
    return novo_no;
}

// --- Implementação das Funções ---

ListaEnc* lista_enc_criar() {
    ListaEnc* l = (ListaEnc*)malloc(sizeof(ListaEnc));
    if (!l) {
        perror("Erro ao alocar memória para a lista");
        return NULL;
    }
    l->inicio = NULL;
    l->tamanho = 0;
    return l;
}

void lista_enc_destruir(ListaEnc** l) {
    if (!l || !*l) return;

    NoListaEnc* atual = (*l)->inicio;
    NoListaEnc* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    free(*l);
    *l = NULL;
}

bool lista_enc_vazia(const ListaEnc* l) {
    if (!l) return true;
    return l->tamanho == 0; // Ou l->inicio == NULL
}

bool lista_enc_inserir_inicio(ListaEnc* l, TipoElementoListaEnc elemento) {
    if (!l) return false;
    NoListaEnc* novo_no = criar_no(elemento);
    if (!novo_no) return false;

    novo_no->proximo = l->inicio;
    l->inicio = novo_no;
    l->tamanho++;
    return true;
}

bool lista_enc_inserir_fim(ListaEnc* l, TipoElementoListaEnc elemento) {
    if (!l) return false;
    NoListaEnc* novo_no = criar_no(elemento);
    if (!novo_no) return false;

    if (lista_enc_vazia(l)) {
        l->inicio = novo_no;
    } else {
        NoListaEnc* atual = l->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }
    l->tamanho++;
    return true;
}

bool lista_enc_inserir_posicao(ListaEnc* l, TipoElementoListaEnc elemento, int posicao) {
    if (!l || posicao < 0 || posicao > l->tamanho) {
        fprintf(stderr, "Erro: Posição de inserção inválida (%d). Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    if (posicao == 0) {
        return lista_enc_inserir_inicio(l, elemento);
    }

    if (posicao == l->tamanho) {
        return lista_enc_inserir_fim(l, elemento);
    }

    // Inserir no meio
    NoListaEnc* novo_no = criar_no(elemento);
    if (!novo_no) return false;

    NoListaEnc* anterior = l->inicio;
    for (int i = 0; i < posicao - 1; i++) {
        anterior = anterior->proximo;
    }

    novo_no->proximo = anterior->proximo;
    anterior->proximo = novo_no;
    l->tamanho++;
    return true;
}

bool lista_enc_remover_inicio(ListaEnc* l, TipoElementoListaEnc* removido) {
    if (!l || lista_enc_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do início.\n");
        return false;
    }

    NoListaEnc* no_removido = l->inicio;
    if (removido) {
        *removido = no_removido->dado;
    }
    l->inicio = no_removido->proximo;
    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_enc_remover_fim(ListaEnc* l, TipoElementoListaEnc* removido) {
    if (!l || lista_enc_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do fim.\n");
        return false;
    }

    // Caso especial: lista com um único elemento
    if (l->tamanho == 1) {
        return lista_enc_remover_inicio(l, removido);
    }

    // Encontra o penúltimo nó
    NoListaEnc* penultimo = l->inicio;
    while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
    }

    NoListaEnc* no_removido = penultimo->proximo;
    if (removido) {
        *removido = no_removido->dado;
    }
    penultimo->proximo = NULL;
    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_enc_remover_posicao(ListaEnc* l, int posicao, TipoElementoListaEnc* removido) {
     if (!l || lista_enc_vazia(l) || posicao < 0 || posicao >= l->tamanho) {
        fprintf(stderr, "Erro: Posição de remoção inválida (%d) ou lista vazia. Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    if (posicao == 0) {
        return lista_enc_remover_inicio(l, removido);
    }

    // Encontra o nó anterior ao que será removido
    NoListaEnc* anterior = l->inicio;
    for (int i = 0; i < posicao - 1; i++) {
        anterior = anterior->proximo;
    }

    NoListaEnc* no_removido = anterior->proximo;
    if (removido) {
        *removido = no_removido->dado;
    }
    anterior->proximo = no_removido->proximo;
    free(no_removido);
    l->tamanho--;
    return true;
}

bool lista_enc_buscar(const ListaEnc* l, TipoElementoListaEnc elemento, int* indice) {
    if (!l) return false;

    NoListaEnc* atual = l->inicio;
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

bool lista_enc_obter_elemento(const ListaEnc* l, int posicao, TipoElementoListaEnc* elemento) {
    if (!l || posicao < 0 || posicao >= l->tamanho) {
         fprintf(stderr, "Erro: Posição inválida (%d) para obter elemento. Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    NoListaEnc* atual = l->inicio;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    if (elemento) {
        *elemento = atual->dado;
    }
    return true;
}

int lista_enc_tamanho(const ListaEnc* l) {
    if (!l) return 0;
    return l->tamanho;
}

void lista_enc_imprimir(const ListaEnc* l) {
    if (!l) {
        printf("Lista inválida.\n");
        return;
    }
    if (lista_enc_vazia(l)) {
        printf("Lista: [] (vazia)\n");
        return;
    }
    printf("Lista: [ ");
    NoListaEnc* atual = l->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
        if (atual != NULL) {
           // printf("-> "); // Opcional: mostrar ligação
        }
    }
    printf("] (Tamanho: %d)\n", l->tamanho);
}