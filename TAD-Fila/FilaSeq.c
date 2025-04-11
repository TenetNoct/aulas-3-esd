// Inclusão dos arquivos de cabeçalho necessários
#include "FilaSeq.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da estrutura da fila sequencial
struct tipo_fila {
    int* vnos;          // Ponteiro para o array de elementos
    int inicio;         // Índice do início da fila
    int fim;            // Índice do fim da fila
    int tamanho;        // Quantidade atual de elementos na fila
    int maximo;         // Capacidade máxima da fila
};

// Função que cria uma fila vazia com o tamanho máximo especificado
tFila * fila_cria_vazia(int maximo) {
    tFila *pf = (tFila*) malloc(sizeof(tFila));      // Aloca memória para a estrutura
    pf->vnos = (int*)malloc(sizeof(int) * maximo);   // Aloca memória para o array
    pf->inicio = 0;                                  // Inicializa com início zero
    pf->fim = 0;                                     // Inicializa com fim zero
    pf->tamanho = 0;                                 // Inicializa com tamanho zero (fila vazia)
    pf->maximo = maximo;                             // Define o tamanho máximo
    return pf;
}

// Função que verifica se a fila está vazia
int fila_vazia(const tFila *pf) {
    return (pf->tamanho == 0);
}

// Função que verifica se a fila está cheia
int fila_cheia(const tFila *pf) {
    return (pf->tamanho == pf->maximo);
}

// Função que percorre e imprime todos os elementos da fila (do início para o fim)
void fila_percorre(const tFila *pf) {
    int i, pos;
    printf("\nFila (do início para o fim):");
    if (fila_vazia(pf)) {
        printf("\nFila vazia!");
        return;
    }
    
    for(i = 0; i < pf->tamanho; i++) {
        pos = (pf->inicio + i) % pf->maximo;         // Cálculo da posição considerando a circularidade
        printf("\n%d", pf->vnos[pos]);
    }
}

// Função que enfileira um novo elemento (enqueue)
int fila_enqueue(tFila *pf, int novo) {
    if (fila_cheia(pf))                              // Verifica se há espaço
        return 0;
    
    pf->vnos[pf->fim] = novo;                       // Insere o elemento no fim
    pf->fim = (pf->fim + 1) % pf->maximo;           // Atualiza o fim (circular)
    pf->tamanho++;                                  // Incrementa o tamanho
    return 1;
}

// Função que desenfileira um elemento (dequeue)
int fila_dequeue(tFila *pf, int *valor) {
    if (fila_vazia(pf))                              // Verifica se está vazia
        return 0;
    
    *valor = pf->vnos[pf->inicio];                  // Retorna o valor removido
    pf->inicio = (pf->inicio + 1) % pf->maximo;     // Atualiza o início (circular)
    pf->tamanho--;                                  // Decrementa o tamanho
    return 1;
}

// Função que consulta o elemento no início da fila sem removê-lo
int fila_consulta_inicio(const tFila *pf, int *valor) {
    if (fila_vazia(pf))                              // Verifica se está vazia
        return 0;
    
    *valor = pf->vnos[pf->inicio];                  // Retorna o valor do início
    return 1;
}

// Função que redimensiona a fila
int fila_redimensiona(tFila *pf, int novo_tamanho) {
    if (novo_tamanho < pf->tamanho)                 // Verifica se o novo tamanho é válido
        return 0;
    
    int *novo_vetor = (int*)malloc(sizeof(int) * novo_tamanho);  // Aloca novo vetor
    if (novo_vetor == NULL)                         // Verifica se alocação falhou
        return 0;
    
    // Copia os elementos para o novo vetor, reorganizando-os
    int i, pos_antiga, pos_nova = 0;
    for(i = 0; i < pf->tamanho; i++) {
        pos_antiga = (pf->inicio + i) % pf->maximo;
        novo_vetor[pos_nova++] = pf->vnos[pos_antiga];
    }
    
    free(pf->vnos);                                 // Libera o vetor antigo
    pf->vnos = novo_vetor;                          // Atualiza ponteiro
    pf->inicio = 0;                                 // Reinicia o início
    pf->fim = pf->tamanho;                          // Atualiza o fim
    pf->maximo = novo_tamanho;                      // Atualiza tamanho máximo
    return 1;
}

// Função que libera a memória alocada para a fila
void fila_libera(tFila *pf) {
    if (pf != NULL) {                                // Verifica se a fila existe
        if (pf->vnos != NULL)                        // Libera array de elementos
            free(pf->vnos);
        free(pf);                                    // Libera estrutura da fila
    }
}