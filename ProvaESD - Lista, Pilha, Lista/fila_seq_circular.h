#ifndef FILA_SEQ_CIRCULAR_H
#define FILA_SEQ_CIRCULAR_H

#include <stdbool.h>

// Define o tipo do dado armazenado na fila (pode ser alterado)
// Usando o mesmo tipo da fila linear para consistência, se aplicável.
#include "fila_seq_linear.h" // Para reutilizar TipoElementoFila

// Estrutura da Fila Sequencial Circular (definição opaca no .h)
typedef struct fila_sequencial_circular FilaSeqCircular;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova fila sequencial circular vazia.
 * @param capacidade A capacidade máxima inicial da fila.
 * @return Ponteiro para a fila criada ou NULL em caso de erro.
 */
FilaSeqCircular* fila_seq_circular_criar(int capacidade);

/**
 * @brief Destroi a fila, liberando toda a memória alocada.
 * @param f Ponteiro para o ponteiro da fila.
 */
void fila_seq_circular_destruir(FilaSeqCircular** f);

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a fila.
 * @return true se a fila estiver vazia, false caso contrário.
 */
bool fila_seq_circular_vazia(const FilaSeqCircular* f);

/**
 * @brief Verifica se a fila está cheia.
 * @param f Ponteiro para a fila.
 * @return true se a fila estiver cheia, false caso contrário.
 */
bool fila_seq_circular_cheia(const FilaSeqCircular* f);

/**
 * @brief Enfileira (insere) um elemento no final da fila.
 *        Utiliza lógica circular para reutilizar espaço.
 * @param f Ponteiro para a fila.
 * @param elemento O elemento a ser enfileirado.
 * @return true se a operação foi bem-sucedida, false caso contrário (fila cheia).
 */
bool fila_seq_circular_enfileirar(FilaSeqCircular* f, TipoElementoFila elemento);

/**
 * @brief Desenfileira (remove) o elemento do início da fila.
 *        Utiliza lógica circular.
 * @param f Ponteiro para a fila.
 * @param elemento Ponteiro para armazenar o elemento desenfileirado (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (fila vazia).
 */
bool fila_seq_circular_desenfileirar(FilaSeqCircular* f, TipoElementoFila* elemento);

/**
 * @brief Consulta o elemento no início da fila sem removê-lo.
 * @param f Ponteiro para a fila.
 * @param elemento Ponteiro para armazenar o elemento do início (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (fila vazia).
 */
bool fila_seq_circular_inicio(const FilaSeqCircular* f, TipoElementoFila* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da fila.
 * @param f Ponteiro para a fila.
 * @return O número de elementos na fila.
 */
int fila_seq_circular_tamanho(const FilaSeqCircular* f);

#endif // FILA_SEQ_CIRCULAR_H