#include "pilha_seq.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura interna da Pilha Sequencial
struct pilha_sequencial {
    TipoElementoPilha* dados;
    int topo_idx;       // Índice do elemento no topo (-1 se vazia)
    int capacidade;     // Capacidade máxima da pilha
};

// --- Implementação das Funções ---

PilhaSeq* pilha_seq_criar(int capacidade) {
    if (capacidade <= 0) {
        fprintf(stderr, "Erro: Capacidade da pilha deve ser positiva.\n");
        return NULL;
    }
    PilhaSeq* p = (PilhaSeq*)malloc(sizeof(PilhaSeq));
    if (!p) {
        perror("Erro ao alocar memória para a pilha");
        return NULL;
    }
    p->dados = (TipoElementoPilha*)malloc(capacidade * sizeof(TipoElementoPilha));
    if (!p->dados) {
        perror("Erro ao alocar memória para os dados da pilha");
        free(p);
        return NULL;
    }
    p->capacidade = capacidade;
    p->topo_idx = -1; // Indica que a pilha está vazia
    return p;
}

void pilha_seq_destruir(PilhaSeq** p) {
    if (p && *p) {
        free((*p)->dados);
        free(*p);
        *p = NULL;
    }
}

bool pilha_seq_vazia(const PilhaSeq* p) {
    if (!p) return true;
    return p->topo_idx == -1;
}

bool pilha_seq_cheia(const PilhaSeq* p) {
    if (!p) return false;
    return p->topo_idx == p->capacidade - 1;
}

bool pilha_seq_empilhar(PilhaSeq* p, TipoElementoPilha elemento) {
    if (!p || pilha_seq_cheia(p)) {
        fprintf(stderr, "Erro: Pilha cheia ou inválida para empilhar.\n");
        // Em uma implementação real, poderia tentar redimensionar aqui.
        return false;
    }
    p->topo_idx++;
    p->dados[p->topo_idx] = elemento;
    return true;
}

bool pilha_seq_desempilhar(PilhaSeq* p, TipoElementoPilha* elemento) {
    if (!p || pilha_seq_vazia(p)) {
        fprintf(stderr, "Erro: Pilha vazia ou inválida para desempilhar.\n");
        return false;
    }
    if (elemento) {
        *elemento = p->dados[p->topo_idx];
    }
    p->topo_idx--;
    return true;
}

bool pilha_seq_topo(const PilhaSeq* p, TipoElementoPilha* elemento) {
    if (!p || pilha_seq_vazia(p)) {
        fprintf(stderr, "Erro: Pilha vazia ou inválida para consultar topo.\n");
        return false;
    }
    if (elemento) {
        *elemento = p->dados[p->topo_idx];
    }
    return true;
}

int pilha_seq_tamanho(const PilhaSeq* p) {
    if (!p) return 0;
    return p->topo_idx + 1;
}