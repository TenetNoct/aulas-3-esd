#include "lista_seq_ord_sr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Para memmove

// Estrutura interna da Lista Sequencial Ordenada Sem Repetição
struct lista_seq_ord_sr {
    TipoElementoListaOrdSR* dados;
    int tamanho;        // Número atual de elementos
    int capacidade;     // Capacidade máxima da lista
};

// Função auxiliar para busca binária (retorna índice ou -1 se não encontrado)
// Ou retorna o índice onde o elemento deveria ser inserido se não encontrado
static int busca_binaria(const ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento) {
    int inicio = 0;
    int fim = l->tamanho - 1;
    int meio;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2; // Evita overflow
        if (l->dados[meio] == elemento) {
            return meio; // Encontrado
        } else if (l->dados[meio] < elemento) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    // Se não encontrou, 'inicio' é a posição onde deveria ser inserido
    return inicio; // Retorna a posição de inserção
}

// --- Implementação das Funções ---

ListaSeqOrdSR* lista_seq_ord_sr_criar(int capacidade) {
    if (capacidade <= 0) {
        fprintf(stderr, "Erro: Capacidade da lista deve ser positiva.\n");
        return NULL;
    }
    ListaSeqOrdSR* l = (ListaSeqOrdSR*)malloc(sizeof(ListaSeqOrdSR));
    if (!l) {
        perror("Erro ao alocar memória para a lista");
        return NULL;
    }
    l->dados = (TipoElementoListaOrdSR*)malloc(capacidade * sizeof(TipoElementoListaOrdSR));
    if (!l->dados) {
        perror("Erro ao alocar memória para os dados da lista");
        free(l);
        return NULL;
    }
    l->capacidade = capacidade;
    l->tamanho = 0;
    return l;
}

void lista_seq_ord_sr_destruir(ListaSeqOrdSR** l) {
    if (l && *l) {
        free((*l)->dados);
        free(*l);
        *l = NULL;
    }
}

bool lista_seq_ord_sr_vazia(const ListaSeqOrdSR* l) {
    if (!l) return true;
    return l->tamanho == 0;
}

bool lista_seq_ord_sr_cheia(const ListaSeqOrdSR* l) {
    if (!l) return false;
    return l->tamanho == l->capacidade;
}

bool lista_seq_ord_sr_inserir(ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento) {
    if (!l || lista_seq_ord_sr_cheia(l)) {
        fprintf(stderr, "Erro: Lista cheia ou inválida para inserir.\n");
        return false;
    }

    int pos_insercao = busca_binaria(l, elemento);

    // Verifica se o elemento já existe na posição encontrada (se a busca encontrou)
    if (pos_insercao < l->tamanho && l->dados[pos_insercao] == elemento) {
         fprintf(stderr, "Erro: Elemento %d já existe na lista.\n", elemento);
        return false; // Elemento repetido
    }

    // Desloca os elementos maiores para a direita para abrir espaço
    // Usa memmove porque as áreas de memória podem sobrepor
    if (pos_insercao < l->tamanho) {
        memmove(&l->dados[pos_insercao + 1], &l->dados[pos_insercao],
                (l->tamanho - pos_insercao) * sizeof(TipoElementoListaOrdSR));
    }

    // Insere o novo elemento na posição correta
    l->dados[pos_insercao] = elemento;
    l->tamanho++;
    return true;
}

bool lista_seq_ord_sr_remover(ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento, TipoElementoListaOrdSR* removido) {
    if (!l || lista_seq_ord_sr_vazia(l)) {
        fprintf(stderr, "Erro: Lista vazia ou inválida para remover.\n");
        return false;
    }

    int indice = busca_binaria(l, elemento);

    // Verifica se o elemento foi realmente encontrado na busca
    if (indice >= l->tamanho || l->dados[indice] != elemento) {
        fprintf(stderr, "Erro: Elemento %d não encontrado para remover.\n", elemento);
        return false; // Elemento não encontrado
    }

    // Guarda o elemento removido, se solicitado
    if (removido) {
        *removido = l->dados[indice];
    }

    // Desloca os elementos à direita do removido para a esquerda
    // Usa memmove porque as áreas de memória podem sobrepor
    if (indice < l->tamanho - 1) {
         memmove(&l->dados[indice], &l->dados[indice + 1],
                (l->tamanho - indice - 1) * sizeof(TipoElementoListaOrdSR));
    }

    l->tamanho--;
    return true;
}

bool lista_seq_ord_sr_buscar(const ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento, int* indice) {
    if (!l) return false;

    int pos = busca_binaria(l, elemento);

    // Verifica se a busca encontrou o elemento na posição retornada
    if (pos < l->tamanho && l->dados[pos] == elemento) {
        if (indice) {
            *indice = pos;
        }
        return true; // Encontrado
    } else {
        return false; // Não encontrado
    }
}

int lista_seq_ord_sr_tamanho(const ListaSeqOrdSR* l) {
    if (!l) return 0;
    return l->tamanho;
}

void lista_seq_ord_sr_imprimir(const ListaSeqOrdSR* l) {
    if (!l) {
        printf("Lista inválida.\n");
        return;
    }
    if (lista_seq_ord_sr_vazia(l)) {
        printf("Lista: [] (vazia)\n");
        return;
    }
    printf("Lista: [ ");
    for (int i = 0; i < l->tamanho; i++) {
        printf("%d ", l->dados[i]);
    }
    printf("] (Tamanho: %d, Capacidade: %d)\n", l->tamanho, l->capacidade);
}