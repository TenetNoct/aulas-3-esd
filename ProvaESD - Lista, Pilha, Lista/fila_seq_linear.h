#ifndef FILA_SEQ_LINEAR_H
#define FILA_SEQ_LINEAR_H

#include <stdbool.h>

// Define o tipo do dado armazenado na fila (pode ser alterado)
typedef int TipoElementoFila;

// Estrutura da Fila Sequencial Linear (definição opaca no .h)
typedef struct fila_sequencial_linear FilaSeqLinear;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova fila sequencial linear vazia.
 * @param capacidade A capacidade máxima inicial da fila.
 * @return Ponteiro para a fila criada ou NULL em caso de erro.
 */
FilaSeqLinear* fila_seq_linear_criar(int capacidade);

/**
 * @brief Destroi a fila, liberando toda a memória alocada.
 * @param f Ponteiro para o ponteiro da fila.
 */
void fila_seq_linear_destruir(FilaSeqLinear** f);

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a fila.
 * @return true se a fila estiver vazia, false caso contrário.
 */
bool fila_seq_linear_vazia(const FilaSeqLinear* f);

/**
 * @brief Verifica se a fila está cheia.
 * @param f Ponteiro para a fila.
 * @return true se a fila estiver cheia, false caso contrário.
 */
bool fila_seq_linear_cheia(const FilaSeqLinear* f);

/**
 * @brief Enfileira (insere) um elemento no final da fila.
 * @param f Ponteiro para a fila.
 * @param elemento O elemento a ser enfileirado.
 * @return true se a operação foi bem-sucedida, false caso contrário (fila cheia).
 */
bool fila_seq_linear_enfileirar(FilaSeqLinear* f, TipoElementoFila elemento);

/**
 * @brief Desenfileira (remove) o elemento do início da fila.
 * @param f Ponteiro para a fila.
 * @param elemento Ponteiro para armazenar o elemento desenfileirado.
 * @return true se a operação foi bem-sucedida, false caso contrário (fila vazia).
 */
bool fila_seq_linear_desenfileirar(FilaSeqLinear* f, TipoElementoFila* elemento);

/**
 * @brief Consulta o elemento no início da fila sem removê-lo.
 * @param f Ponteiro para a fila.
 * @param elemento Ponteiro para armazenar o elemento do início.
 * @return true se a operação foi bem-sucedida, false caso contrário (fila vazia).
 */
bool fila_seq_linear_inicio(const FilaSeqLinear* f, TipoElementoFila* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da fila.
 * @param f Ponteiro para a fila.
 * @return O número de elementos na fila.
 */
int fila_seq_linear_tamanho(const FilaSeqLinear* f);

#endif // FILA_SEQ_LINEAR_H