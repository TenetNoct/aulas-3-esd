#include "fila_seq_linear.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Para memcpy

// Estrutura interna da Fila Sequencial Linear
struct fila_sequencial_linear {
    TipoElementoFila* dados;
    int inicio;         // Índice do primeiro elemento
    int fim;            // Índice da próxima posição livre (após o último elemento)
    int tamanho;        // Número atual de elementos
    int capacidade;     // Capacidade máxima da fila
};

// --- Implementação das Funções ---

FilaSeqLinear* fila_seq_linear_criar(int capacidade) {
    if (capacidade <= 0) {
        fprintf(stderr, "Erro: Capacidade da fila deve ser positiva.\n");
        return NULL;
    }
    FilaSeqLinear* f = (FilaSeqLinear*)malloc(sizeof(FilaSeqLinear));
    if (!f) {
        perror("Erro ao alocar memória para a fila");
        return NULL;
    }
    f->dados = (TipoElementoFila*)malloc(capacidade * sizeof(TipoElementoFila));
    if (!f->dados) {
        perror("Erro ao alocar memória para os dados da fila");
        free(f);
        return NULL;
    }
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void fila_seq_linear_destruir(FilaSeqLinear** f) {
    if (f && *f) {
        free((*f)->dados);
        free(*f);
        *f = NULL;
    }
}

bool fila_seq_linear_vazia(const FilaSeqLinear* f) {
    if (!f) return true;
    return f->tamanho == 0;
}

bool fila_seq_linear_cheia(const FilaSeqLinear* f) {
    if (!f) return false;
    return f->tamanho == f->capacidade;
}

bool fila_seq_linear_enfileirar(FilaSeqLinear* f, TipoElementoFila elemento) {
    if (!f || fila_seq_linear_cheia(f)) {
        fprintf(stderr, "Erro: Fila cheia ou inválida para enfileirar.\n");
        // Em uma implementação real, poderia tentar redimensionar aqui.
        return false;
    }
    // Verifica se há espaço no final do vetor
    if (f->fim < f->capacidade) {
        f->dados[f->fim] = elemento;
        f->fim++;
        f->tamanho++;
        return true;
    } else {
        // Fila cheia no sentido de não ter mais espaço *contíguo* no final,
        // mesmo que haja espaço no início após desenfileiramentos.
        // A fila linear tem essa limitação.
        fprintf(stderr, "Erro: Fim do vetor alcançado na fila linear.\n");
        return false;
    }
}

bool fila_seq_linear_desenfileirar(FilaSeqLinear* f, TipoElementoFila* elemento) {
    if (!f || fila_seq_linear_vazia(f)) {
        fprintf(stderr, "Erro: Fila vazia ou inválida para desenfileirar.\n");
        return false;
    }
    if (elemento) {
        *elemento = f->dados[f->inicio];
    }
    f->inicio++; // Apenas avança o início, o espaço não é reutilizado imediatamente
    f->tamanho--;

    // Opcional: Se a fila ficar vazia, resetar os índices para reutilizar o espaço
    if (fila_seq_linear_vazia(f)) {
        f->inicio = 0;
        f->fim = 0;
    }

    return true;
}

bool fila_seq_linear_inicio(const FilaSeqLinear* f, TipoElementoFila* elemento) {
    if (!f || fila_seq_linear_vazia(f)) {
        fprintf(stderr, "Erro: Fila vazia ou inválida para consultar início.\n");
        return false;
    }
    if (elemento) {
        *elemento = f->dados[f->inicio];
    }
    return true;
}

int fila_seq_linear_tamanho(const FilaSeqLinear* f) {
    if (!f) return 0;
    return f->tamanho;
}