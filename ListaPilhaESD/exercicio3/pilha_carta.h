#ifndef PILHA_CARTA_H
#define PILHA_CARTA_H

#include <stdbool.h> // Inclui a biblioteca para usar o tipo booleano (true/false)

// Define os naipes possíveis para uma carta
typedef enum {
    COPAS,    // ♥
    OUROS,    // ♦
    ESPADAS,  // ♠
    PAUS      // ♣
} Naipe;

// Define a estrutura para representar uma carta de baralho
typedef struct {
    int valor;  // Valor da carta (1=Ás, 2-10, 11=Valete, 12=Dama, 13=Rei)
    Naipe naipe; // Naipe da carta
    bool virada_para_cima; // Indica se a carta está visível ou não no jogo
} Carta;

// Define o tipo de elemento que a pilha armazenará como sendo 'Carta'
// Usado para representar os montes de cartas no jogo Paciência.
typedef Carta TipoElementoPilha;

// Estrutura opaca da Pilha Sequencial para Cartas (oculta os detalhes da implementação)
typedef struct pilha_sequencial PilhaCarta;

// --- Funções do TAD Pilha Sequencial para Cartas ---

/**
 * @brief Cria uma nova pilha sequencial para armazenar cartas.
 * 
 * @param capacidade A capacidade máxima inicial da pilha (quantas cartas pode armazenar).
 * @return PilhaCarta* Um ponteiro para a pilha criada ou NULL se ocorrer um erro (ex: memória insuficiente).
 */
PilhaCarta* pilha_carta_criar(int capacidade);

/**
 * @brief Destrói uma pilha de cartas, liberando toda a memória alocada por ela.
 * 
 * @param p Um ponteiro para o ponteiro da pilha a ser destruída. 
 *          Após a destruição, o ponteiro original apontará para NULL para evitar uso indevido.
 */
void pilha_carta_destruir(PilhaCarta** p);

/**
 * @brief Verifica se a pilha de cartas está vazia.
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha não contiver nenhuma carta, false caso contrário.
 */
bool pilha_carta_vazia(const PilhaCarta* p);

/**
 * @brief Verifica se a pilha de cartas está cheia (atingiu sua capacidade máxima).
 * 
 * @param p A pilha a ser verificada.
 * @return true Se a pilha estiver cheia, false caso contrário.
 */
bool pilha_carta_cheia(const PilhaCarta* p);

/**
 * @brief Empilha (insere) uma carta no topo da pilha.
 * 
 * @param p A pilha onde a carta será inserida.
 * @param elemento A carta (do tipo TipoElementoPilha) a ser empilhada.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver cheia ou for inválida.
 */
bool pilha_carta_empilhar(PilhaCarta* p, TipoElementoPilha elemento);

/**
 * @brief Desempilha (remove) a carta do topo da pilha.
 * 
 * @param p A pilha de onde a carta será removida.
 * @param elemento Um ponteiro para uma variável Carta onde a carta removida será armazenada.
 *                 Se não precisar da carta removida, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_carta_desempilhar(PilhaCarta* p, TipoElementoPilha* elemento);

/**
 * @brief Consulta a carta no topo da pilha sem removê-la.
 * 
 * @param p A pilha a ser consultada.
 * @param elemento Um ponteiro para uma variável Carta onde a carta do topo será armazenada.
 *                 Se não precisar da carta, pode passar NULL.
 * @return true Se a operação foi bem-sucedida, false se a pilha estiver vazia ou for inválida.
 */
bool pilha_carta_topo(const PilhaCarta* p, TipoElementoPilha* elemento);

/**
 * @brief Retorna o número de cartas atualmente na pilha.
 * 
 * @param p A pilha.
 * @return int O número de cartas na pilha (0 se estiver vazia).
 */
int pilha_carta_tamanho(const PilhaCarta* p);

#endif // PILHA_CARTA_H