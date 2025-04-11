// Inclusão dos arquivos de cabeçalho necessários
#include "PilhaSeq.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da estrutura da pilha sequencial
struct tipo_pilha {
    int* vnos;          // Ponteiro para o array de elementos
    int topo;           // Índice do topo da pilha (também representa a quantidade de elementos)
    int maximo;         // Capacidade máxima da pilha
};

// Função que cria uma pilha vazia com o tamanho máximo especificado
tPilha * pilha_cria_vazia(int maximo) {
    tPilha *pp = (tPilha*) malloc(sizeof(tPilha));     // Aloca memória para a estrutura
    pp->vnos = (int*)malloc(sizeof(int) * maximo);    // Aloca memória para o array
    pp->topo = 0;                                     // Inicializa com topo zero (pilha vazia)
    pp->maximo = maximo;                              // Define o tamanho máximo
    return pp;
}

// Função que verifica se a pilha está vazia
int pilha_vazia(const tPilha *pp) {
    return (pp->topo == 0);
}

// Função que verifica se a pilha está cheia
int pilha_cheia(const tPilha *pp) {
    return (pp->topo == pp->maximo);
}

// Função que percorre e imprime todos os elementos da pilha (do topo para a base)
void pilha_percorre(const tPilha *pp) {
    int i;
    printf("\nPilha (do topo para a base):");
    for(i = pp->topo - 1; i >= 0; i--)
        printf("\n%d", pp->vnos[i]);
    if (pilha_vazia(pp))
        printf("\nPilha vazia!");
}

// Função que empilha um novo elemento (push)
int pilha_push(tPilha *pp, int novo) {
    if (pilha_cheia(pp))                              // Verifica se há espaço
        return 0;
    
    pp->vnos[pp->topo] = novo;                       // Insere o elemento no topo
    pp->topo++;                                      // Incrementa o topo
    return 1;
}

// Função que desempilha um elemento (pop)
int pilha_pop(tPilha *pp, int *valor) {
    if (pilha_vazia(pp))                              // Verifica se está vazia
        return 0;
    
    pp->topo--;                                      // Decrementa o topo
    *valor = pp->vnos[pp->topo];                     // Retorna o valor removido
    return 1;
}

// Função que consulta o elemento no topo da pilha sem removê-lo
int pilha_consulta_topo(const tPilha *pp, int *valor) {
    if (pilha_vazia(pp))                              // Verifica se está vazia
        return 0;
    
    *valor = pp->vnos[pp->topo - 1];                 // Retorna o valor do topo
    return 1;
}

// Função que redimensiona a pilha
int pilha_redimensiona(tPilha *pp, int novo_tamanho) {
    if (novo_tamanho < pp->topo)                     // Verifica se o novo tamanho é válido
        return 0;
    
    int *novo_vetor = (int*)realloc(pp->vnos, sizeof(int) * novo_tamanho);  // Realoca memória
    if (novo_vetor == NULL)                          // Verifica se alocação falhou
        return 0;
    
    pp->vnos = novo_vetor;                          // Atualiza ponteiro
    pp->maximo = novo_tamanho;                      // Atualiza tamanho máximo
    return 1;
}

// Função que libera a memória alocada para a pilha
void pilha_libera(tPilha *pp) {
    if (pp != NULL) {                                // Verifica se a pilha existe
        if (pp->vnos != NULL)                        // Libera array de elementos
            free(pp->vnos);
        free(pp);                                    // Libera estrutura da pilha
    }
}