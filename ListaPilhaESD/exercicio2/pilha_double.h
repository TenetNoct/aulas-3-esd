#ifndef PILHA_DOUBLE_H
#define PILHA_DOUBLE_H

#include <stdbool.h> // Inclui a biblioteca para usar o tipo booleano (true/false)

// Define o tipo de elemento que a pilha armazenará como sendo 'double'
// Usado para armazenar os operandos na calculadora pós-fixada.
typedef double TipoElementoPilha; 

// Estrutura opaca da Pilha Sequencial para doubles (oculta os detalhes da implementação)
// O usuário do TAD não precisa saber como a pilha é implementada internamente.
typedef struct pilha_sequencial PilhaDouble; 

// --- Funções do TAD Pilha Sequencial para Doubles ---

/**
 * @brief Cria uma nova pilha sequencial para armazenar números double.
 * 
 * @param capacidade A capacidade máxima inicial da pilha (quantos doubles pode armazenar).
 * @return PilhaDouble* Um ponteiro para a pilha criada ou NULL se ocorrer um erro (ex: memória insuficiente).
 */
PilhaDouble* pilha_double_criar(int capacidade);

/**
 * @brief Destrói uma pilha de doubles, liberando toda a memória alocada por ela.
 * 
 * @param p Um ponteiro para o ponteiro da pilha a ser destruída. 
 *          Após a destruição, o ponteiro original apontará para NULL para evitar uso indevido.
 */
void pilha_double_destruir(PilhaDouble** p);

/**
 * @brief Verifica se a pilha de doubles está vazia.
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha não contiver nenhum double, false caso contrário.
 */
bool pilha_double_vazia(const PilhaDouble* p);

/**
 * @brief Verifica se a pilha de doubles está cheia (atingiu sua capacidade máxima).
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha estiver cheia, false caso contrário.
 */
bool pilha_double_cheia(const PilhaDouble* p);

/**
 * @brief Empilha (insere) um double no topo da pilha.
 * 
 * @param p A pilha onde o double será inserido.
 * @param elemento O double (do tipo TipoElementoPilha) a ser empilhado.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver cheia ou for inválida.
 */
bool pilha_double_empilhar(PilhaDouble* p, TipoElementoPilha elemento);

/**
 * @brief Desempilha (remove) o double do topo da pilha.
 * 
 * @param p A pilha de onde o double será removido.
 * @param elemento Um ponteiro para uma variável double onde o valor removido será armazenado.
 *                 Se não precisar do valor removido, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_double_desempilhar(PilhaDouble* p, TipoElementoPilha* elemento);

/**
 * @brief Consulta o double no topo da pilha sem removê-lo.
 * 
 * @param p A pilha a ser consultada.
 * @param elemento Um ponteiro para uma variável double onde o valor do topo será armazenado.
 *                 Se não precisar do valor, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_double_topo(const PilhaDouble* p, TipoElementoPilha* elemento);

/**
 * @brief Retorna o número de doubles atualmente na pilha.
 * 
 * @param p A pilha.
 * @return int O número de doubles na pilha (0 se estiver vazia).
 */
int pilha_double_tamanho(const PilhaDouble* p);

#endif // PILHA_DOUBLE_H