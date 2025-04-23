#include "fila_seq_circular.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura interna da Fila Sequencial Circular
struct fila_sequencial_circular {
    TipoElementoFila* dados;
    int inicio;         // Índice do primeiro elemento
    int fim;            // Índice da próxima posição livre
    int tamanho;        // Número atual de elementos
    int capacidade;     // Capacidade máxima da fila (tamanho do vetor)
};

// --- Implementação das Funções ---

FilaSeqCircular* fila_seq_circular_criar(int capacidade) {
    if (capacidade <= 0) {
        fprintf(stderr, "Erro: Capacidade da fila deve ser positiva.\n");
        return NULL;
    }
    // Aloca um espaço extra para diferenciar fila cheia de vazia
    int capacidade_real = capacidade + 1;
    FilaSeqCircular* f = (FilaSeqCircular*)malloc(sizeof(FilaSeqCircular));
    if (!f) {
        perror("Erro ao alocar memória para a fila");
        return NULL;
    }
    f->dados = (TipoElementoFila*)malloc(capacidade_real * sizeof(TipoElementoFila));
    if (!f->dados) {
        perror("Erro ao alocar memória para os dados da fila");
        free(f);
        return NULL;
    }
    f->capacidade = capacidade_real;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void fila_seq_circular_destruir(FilaSeqCircular** f) {
    if (f && *f) {
        free((*f)->dados);
        free(*f);
        *f = NULL;
    }
}

bool fila_seq_circular_vazia(const FilaSeqCircular* f) {
    if (!f) return true;
    return f->tamanho == 0; // Ou f->inicio == f->fim
}

bool fila_seq_circular_cheia(const FilaSeqCircular* f) {
    if (!f) return false;
    // Fila cheia quando o próximo índice do fim, calculado circularmente,
    // coincide com o início. Usa-se a capacidade real (capacidade + 1).
    return (f->fim + 1) % f->capacidade == f->inicio;
}

bool fila_seq_circular_enfileirar(FilaSeqCircular* f, TipoElementoFila elemento) {
    if (!f || fila_seq_circular_cheia(f)) {
        fprintf(stderr, "Erro: Fila cheia ou inválida para enfileirar.\n");
        return false;
    }
    f->dados[f->fim] = elemento;
    f->fim = (f->fim + 1) % f->capacidade; // Avança o fim circularmente
    f->tamanho++;
    return true;
}

bool fila_seq_circular_desenfileirar(FilaSeqCircular* f, TipoElementoFila* elemento) {
    if (!f || fila_seq_circular_vazia(f)) {
        fprintf(stderr, "Erro: Fila vazia ou inválida para desenfileirar.\n");
        return false;
    }
    if (elemento) {
        *elemento = f->dados[f->inicio];
    }
    f->inicio = (f->inicio + 1) % f->capacidade; // Avança o início circularmente
    f->tamanho--;
    return true;
}

bool fila_seq_circular_inicio(const FilaSeqCircular* f, TipoElementoFila* elemento) {
    if (!f || fila_seq_circular_vazia(f)) {
        fprintf(stderr, "Erro: Fila vazia ou inválida para consultar início.\n");
        return false;
    }
    if (elemento) {
        *elemento = f->dados[f->inicio];
    }
    return true;
}

int fila_seq_circular_tamanho(const FilaSeqCircular* f) {
    if (!f) return 0;
    return f->tamanho;
    /* Alternativa (cálculo direto pelos índices):
    if (f->fim >= f->inicio) {
        return f->fim - f->inicio;
    } else {
        return f->capacidade - f->inicio + f->fim;
    }
    */
}