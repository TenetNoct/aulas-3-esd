#ifndef PILHA_CHEQUE_H
#define PILHA_CHEQUE_H

#include <stdbool.h> // Inclui a biblioteca para usar o tipo booleano (true/false)

// Define a estrutura para representar um cheque
typedef struct {
    int numero;     // Número do cheque
    double valor;   // Valor do cheque
} Cheque; // Define 'Cheque' como um novo tipo de dado

// Define o tipo de elemento que a pilha armazenará como sendo a estrutura Cheque
typedef Cheque TipoElementoPilha; 

// Estrutura opaca da Pilha Sequencial (oculta os detalhes da implementação)
// O usuário do TAD não precisa saber como a pilha é implementada internamente.
typedef struct pilha_sequencial PilhaCheque; 

// --- Funções do TAD Pilha Sequencial para Cheques ---

/**
 * @brief Cria uma nova pilha sequencial para armazenar cheques.
 * 
 * @param capacidade A capacidade máxima inicial da pilha (quantos cheques pode armazenar).
 * @return PilhaCheque* Um ponteiro para a pilha criada ou NULL se ocorrer um erro (ex: memória insuficiente).
 */
PilhaCheque* pilha_cheque_criar(int capacidade);

/**
 * @brief Destrói uma pilha de cheques, liberando toda a memória alocada por ela.
 * 
 * @param p Um ponteiro para o ponteiro da pilha a ser destruída. 
 *          Após a destruição, o ponteiro original apontará para NULL para evitar uso indevido.
 */
void pilha_cheque_destruir(PilhaCheque** p);

/**
 * @brief Verifica se a pilha de cheques está vazia.
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha não contiver nenhum cheque, false caso contrário.
 */
bool pilha_cheque_vazia(const PilhaCheque* p);

/**
 * @brief Verifica se a pilha de cheques está cheia (atingiu sua capacidade máxima).
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha estiver cheia, false caso contrário.
 */
bool pilha_cheque_cheia(const PilhaCheque* p);

/**
 * @brief Empilha (insere) um cheque no topo da pilha.
 * 
 * @param p A pilha onde o cheque será inserido.
 * @param elemento O cheque (do tipo TipoElementoPilha, que é Cheque) a ser empilhado.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver cheia ou for inválida.
 */
bool pilha_cheque_empilhar(PilhaCheque* p, TipoElementoPilha elemento);

/**
 * @brief Desempilha (remove) o cheque do topo da pilha.
 * 
 * @param p A pilha de onde o cheque será removido.
 * @param elemento Um ponteiro para uma variável Cheque onde o cheque removido será armazenado.
 *                 Se não precisar do valor removido, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_cheque_desempilhar(PilhaCheque* p, TipoElementoPilha* elemento);

/**
 * @brief Consulta o cheque no topo da pilha sem removê-lo.
 * 
 * @param p A pilha a ser consultada.
 * @param elemento Um ponteiro para uma variável Cheque onde o cheque do topo será armazenado.
 *                 Se não precisar do valor, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_cheque_topo(const PilhaCheque* p, TipoElementoPilha* elemento);

/**
 * @brief Retorna o número de cheques atualmente na pilha.
 * 
 * @param p A pilha.
 * @return int O número de cheques na pilha (0 se estiver vazia).
 */
int pilha_cheque_tamanho(const PilhaCheque* p);

#endif // PILHA_CHEQUE_H