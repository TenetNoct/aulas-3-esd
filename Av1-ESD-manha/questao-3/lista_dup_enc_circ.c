#include "lista_dup_enc_circ.h"
#include <stdlib.h>
#include <stdio.h>

// Função auxiliar para criar um novo nó
static NoListaDupEncCirc* criar_no_dup_circ(TipoElementoListaDupEncCirc elemento) {
    NoListaDupEncCirc* novo_no = (NoListaDupEncCirc*)malloc(sizeof(NoListaDupEncCirc));
    if (!novo_no) {
        perror("Erro ao alocar memória para novo nó duplo circular");
        return NULL;
    }
    novo_no->dado = elemento;
    novo_no->proximo = NULL; // Será ajustado na inserção
    novo_no->anterior = NULL; // Será ajustado na inserção
    return novo_no;
}

// Função auxiliar para obter o nó em uma posição específica (0-indexed)
// Percorre a partir do nó cabeça->proximo
static NoListaDupEncCirc* obter_no_posicao_circ(const ListaDupEncCirc* l, int posicao) {
    if (!l || posicao < 0 || posicao >= l->tamanho) {
        return NULL; // Posição inválida
    }

    NoListaDupEncCirc* atual = l->cabeca->proximo; // Começa do primeiro elemento real
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }
    return atual;
}

// --- Implementação das Funções ---

ListaDupEncCirc* lista_dup_enc_circ_criar() {
    ListaDupEncCirc* l = (ListaDupEncCirc*)malloc(sizeof(ListaDupEncCirc));
    if (!l) {
        perror("Erro ao alocar memória para a lista dupla circular");
        return NULL;
    }
    // Cria o nó sentinela (cabeça)
    l->cabeca = (NoListaDupEncCirc*)malloc(sizeof(NoListaDupEncCirc));
    if (!l->cabeca) {
        perror("Erro ao alocar memória para o nó cabeça");
        free(l);
        return NULL;
    }
    // Nó cabeça aponta para si mesmo quando a lista está vazia
    l->cabeca->proximo = l->cabeca;
    l->cabeca->anterior = l->cabeca;
    l->tamanho = 0;
    // O dado do nó cabeça não é usado, pode ser inicializado com 0 ou lixo
    // l->cabeca->dado = 0; // Opcional
    return l;
}

void lista_dup_enc_circ_destruir(ListaDupEncCirc** l) {
    if (!l || !*l) return;

    NoListaDupEncCirc* atual = (*l)->cabeca->proximo;
    while (atual != (*l)->cabeca) { // Percorre até voltar ao nó cabeça
        NoListaDupEncCirc* proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    free((*l)->cabeca); // Libera o nó cabeça
    free(*l);           // Libera a estrutura da lista
    *l = NULL;
}

bool lista_dup_enc_circ_vazia(const ListaDupEncCirc* l) {
    if (!l) return true;
    return l->tamanho == 0; // Ou l->cabeca->proximo == l->cabeca
}

// Função auxiliar interna para inserir um nó entre dois outros nós
static void inserir_entre(NoListaDupEncCirc* anterior, NoListaDupEncCirc* novo_no, NoListaDupEncCirc* proximo) {
    novo_no->anterior = anterior;
    novo_no->proximo = proximo;
    anterior->proximo = novo_no;
    proximo->anterior = novo_no;
}

bool lista_dup_enc_circ_inserir_inicio(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento) {
    if (!l) return false;
    NoListaDupEncCirc* novo_no = criar_no_dup_circ(elemento);
    if (!novo_no) return false;

    // Insere entre o nó cabeça e o primeiro elemento atual
    inserir_entre(l->cabeca, novo_no, l->cabeca->proximo);
    l->tamanho++;
    return true;
}

bool lista_dup_enc_circ_inserir_fim(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento) {
    if (!l) return false;
    NoListaDupEncCirc* novo_no = criar_no_dup_circ(elemento);
    if (!novo_no) return false;

    // Insere entre o último elemento atual e o nó cabeça
    inserir_entre(l->cabeca->anterior, novo_no, l->cabeca);
    l->tamanho++;
    return true;
}

bool lista_dup_enc_circ_inserir_posicao(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int posicao) {
    if (!l || posicao < 0 || posicao > l->tamanho) {
        fprintf(stderr, "Erro: Posição de inserção inválida (%d). Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    if (posicao == 0) {
        return lista_dup_enc_circ_inserir_inicio(l, elemento);
    }
    if (posicao == l->tamanho) {
        return lista_dup_enc_circ_inserir_fim(l, elemento);
    }

    // Inserir no meio
    NoListaDupEncCirc* novo_no = criar_no_dup_circ(elemento);
    if (!novo_no) return false;

    // Encontra o nó que ficará *antes* do novo nó
    NoListaDupEncCirc* no_anterior = obter_no_posicao_circ(l, posicao - 1);
    if (!no_anterior) return false; // Segurança

    inserir_entre(no_anterior, novo_no, no_anterior->proximo);
    l->tamanho++;
    return true;
}

// Função auxiliar interna para remover um nó
static void remover_no(NoListaDupEncCirc* no_removido) {
    NoListaDupEncCirc* anterior = no_removido->anterior;
    NoListaDupEncCirc* proximo = no_removido->proximo;
    anterior->proximo = proximo;
    proximo->anterior = anterior;
    free(no_removido);
}

bool lista_dup_enc_circ_remover_inicio(ListaDupEncCirc* l, TipoElementoListaDupEncCirc* removido) {
    if (!l || lista_dup_enc_circ_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do início.\n");
        return false;
    }

    NoListaDupEncCirc* no_removido = l->cabeca->proximo; // O primeiro elemento real
    if (removido) {
        *removido = no_removido->dado;
    }
    remover_no(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_circ_remover_fim(ListaDupEncCirc* l, TipoElementoListaDupEncCirc* removido) {
    if (!l || lista_dup_enc_circ_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover do fim.\n");
        return false;
    }

    NoListaDupEncCirc* no_removido = l->cabeca->anterior; // O último elemento real
    if (removido) {
        *removido = no_removido->dado;
    }
    remover_no(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_circ_remover_posicao(ListaDupEncCirc* l, int posicao, TipoElementoListaDupEncCirc* removido) {
     if (!l || lista_dup_enc_circ_vazia(l) || posicao < 0 || posicao >= l->tamanho) {
        fprintf(stderr, "Erro: Posição de remoção inválida (%d) ou lista vazia. Tamanho: %d\n", posicao, l->tamanho);
        return false;
    }

    NoListaDupEncCirc* no_removido = obter_no_posicao_circ(l, posicao);
    if (!no_removido) return false; // Segurança

    if (removido) {
        *removido = no_removido->dado;
    }
    remover_no(no_removido);
    l->tamanho--;
    return true;
}

bool lista_dup_enc_circ_buscar(const ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int* indice) {
    if (!l) return false;

    NoListaDupEncCirc* atual = l->cabeca->proximo;
    int i = 0;
    while (atual != l->cabeca) { // Percorre até voltar ao nó cabeça
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

bool lista_dup_enc_circ_obter_elemento(const ListaDupEncCirc* l, int posicao, TipoElementoListaDupEncCirc* elemento) {
    NoListaDupEncCirc* no = obter_no_posicao_circ(l, posicao);
    if (!no) {
         fprintf(stderr, "Erro: Posição inválida (%d) para obter elemento. Tamanho: %d\n", posicao, l ? l->tamanho : -1);
        return false;
    }

    if (elemento) {
        *elemento = no->dado;
    }
    return true;
}

int lista_dup_enc_circ_tamanho(const ListaDupEncCirc* l) {
    if (!l) return 0;
    return l->tamanho;
}

void lista_dup_enc_circ_imprimir(const ListaDupEncCirc* l) {
    if (!l) {
        printf("Lista dupla circular inválida.\n");
        return;
    }
    if (lista_dup_enc_circ_vazia(l)) {
        printf("Lista Circular: [] (vazia)\n");
        return;
    }
    printf("Lista Circular: [ ");
    NoListaDupEncCirc* atual = l->cabeca->proximo;
    while (atual != l->cabeca) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("] (Tamanho: %d)\n", l->tamanho);
}


ListaDupEncCirc* lista_dup_enc_circ_copia_sublista(const ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int n) {
    if (!l || n <= 0) return NULL;

    int indice;
    if (!lista_dup_enc_circ_buscar(l, elemento, &indice)) return NULL;

    if (indice < n) return NULL;

    ListaDupEncCirc* nova_lista = lista_dup_enc_circ_criar();
    if (!nova_lista) return NULL;

    NoListaDupEncCirc* atual = obter_no_posicao_circ(l, indice - n);
    for (int i = 0; i < n; i++) {
        lista_dup_enc_circ_inserir_fim(nova_lista, atual->dado);
        atual = atual->proximo;
    }

    return nova_lista;
}