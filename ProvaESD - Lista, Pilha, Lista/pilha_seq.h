#ifndef PILHA_SEQ_H
#define PILHA_SEQ_H

#include <stdbool.h>

// Define o tipo do dado armazenado na pilha (pode ser alterado)
typedef int TipoElementoPilha;

// Estrutura da Pilha Sequencial (definição opaca no .h)
typedef struct pilha_sequencial PilhaSeq;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova pilha sequencial vazia.
 * @param capacidade A capacidade máxima inicial da pilha.
 * @return Ponteiro para a pilha criada ou NULL em caso de erro.
 */
PilhaSeq* pilha_seq_criar(int capacidade);

/**
 * @brief Destroi a pilha, liberando toda a memória alocada.
 * @param p Ponteiro para o ponteiro da pilha.
 */
void pilha_seq_destruir(PilhaSeq** p);

/**
 * @brief Verifica se a pilha está vazia.
 * @param p Ponteiro para a pilha.
 * @return true se a pilha estiver vazia, false caso contrário.
 */
bool pilha_seq_vazia(const PilhaSeq* p);

/**
 * @brief Verifica se a pilha está cheia.
 * @param p Ponteiro para a pilha.
 * @return true se a pilha estiver cheia, false caso contrário.
 */
bool pilha_seq_cheia(const PilhaSeq* p);

/**
 * @brief Empilha (insere) um elemento no topo da pilha.
 * @param p Ponteiro para a pilha.
 * @param elemento O elemento a ser empilhado.
 * @return true se a operação foi bem-sucedida, false caso contrário (pilha cheia).
 */
bool pilha_seq_empilhar(PilhaSeq* p, TipoElementoPilha elemento);

/**
 * @brief Desempilha (remove) o elemento do topo da pilha.
 * @param p Ponteiro para a pilha.
 * @param elemento Ponteiro para armazenar o elemento desempilhado.
 * @return true se a operação foi bem-sucedida, false caso contrário (pilha vazia).
 */
bool pilha_seq_desempilhar(PilhaSeq* p, TipoElementoPilha* elemento);

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * @param p Ponteiro para a pilha.
 * @param elemento Ponteiro para armazenar o elemento do topo.
 * @return true se a operação foi bem-sucedida, false caso contrário (pilha vazia).
 */
bool pilha_seq_topo(const PilhaSeq* p, TipoElementoPilha* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da pilha.
 * @param p Ponteiro para a pilha.
 * @return O número de elementos na pilha.
 */
int pilha_seq_tamanho(const PilhaSeq* p);

#endif // PILHA_SEQ_H