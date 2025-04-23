#ifndef PILHA_SEQ_H
#define PILHA_SEQ_H

#include <stdbool.h>

// Defina o tipo de elemento que a pilha armazenará
// Pode ser int, float, char, struct, etc.
// Para o exercício 4 (Jogo da Roleta), usaremos int para o número do jogador.
typedef int TipoElementoPilha;

// Estrutura da Pilha Sequencial (oculta a implementação)
typedef struct pilha_sequencial PilhaSeq;

// --- Funções do TAD Pilha Sequencial ---

/**
 * @brief Cria uma nova pilha sequencial com uma capacidade inicial.
 * 
 * @param capacidade A capacidade máxima inicial da pilha.
 * @return PilhaSeq* Um ponteiro para a pilha criada ou NULL em caso de erro.
 */
PilhaSeq* pilha_seq_criar(int capacidade);

/**
 * @brief Destrói uma pilha sequencial, liberando toda a memória alocada.
 * 
 * @param p Um ponteiro para o ponteiro da pilha a ser destruída. O ponteiro original será setado para NULL.
 */
void pilha_seq_destruir(PilhaSeq** p);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha estiver vazia, false caso contrário.
 */
bool pilha_seq_vazia(const PilhaSeq* p);

/**
 * @brief Verifica se a pilha está cheia.
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha estiver cheia, false caso contrário.
 */
bool pilha_seq_cheia(const PilhaSeq* p);

/**
 * @brief Empilha (insere) um elemento no topo da pilha.
 * 
 * @param p A pilha onde o elemento será inserido.
 * @param elemento O elemento a ser empilhado.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver cheia ou inválida.
 */
bool pilha_seq_empilhar(PilhaSeq* p, TipoElementoPilha elemento);

/**
 * @brief Desempilha (remove) o elemento do topo da pilha.
 * 
 * @param p A pilha de onde o elemento será removido.
 * @param elemento Um ponteiro para armazenar o elemento removido (opcional, pode ser NULL).
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou inválida.
 */
bool pilha_seq_desempilhar(PilhaSeq* p, TipoElementoPilha* elemento);

/**
 * @brief Consulta o elemento no topo da pilha sem removê-lo.
 * 
 * @param p A pilha a ser consultada.
 * @param elemento Um ponteiro para armazenar o elemento do topo (opcional, pode ser NULL).
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou inválida.
 */
bool pilha_seq_topo(const PilhaSeq* p, TipoElementoPilha* elemento);

/**
 * @brief Retorna o número de elementos atualmente na pilha.
 * 
 * @param p A pilha.
 * @return int O número de elementos na pilha.
 */
int pilha_seq_tamanho(const PilhaSeq* p);

#endif // PILHA_SEQ_H