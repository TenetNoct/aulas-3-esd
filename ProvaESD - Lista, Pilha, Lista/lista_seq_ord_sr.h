#ifndef LISTA_SEQ_ORD_SR_H
#define LISTA_SEQ_ORD_SR_H

#include <stdbool.h>

// Define o tipo do dado armazenado na lista (pode ser alterado)
typedef int TipoElementoListaOrdSR;

// Estrutura da Lista Sequencial Ordenada Sem Repetição (definição opaca no .h)
typedef struct lista_seq_ord_sr ListaSeqOrdSR;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova lista sequencial ordenada sem repetição vazia.
 * @param capacidade A capacidade máxima inicial da lista.
 * @return Ponteiro para a lista criada ou NULL em caso de erro.
 */
ListaSeqOrdSR* lista_seq_ord_sr_criar(int capacidade);

/**
 * @brief Destroi a lista, liberando toda a memória alocada.
 * @param l Ponteiro para o ponteiro da lista.
 */
void lista_seq_ord_sr_destruir(ListaSeqOrdSR** l);

/**
 * @brief Verifica se a lista está vazia.
 * @param l Ponteiro para a lista.
 * @return true se a lista estiver vazia, false caso contrário.
 */
bool lista_seq_ord_sr_vazia(const ListaSeqOrdSR* l);

/**
 * @brief Verifica se a lista está cheia.
 * @param l Ponteiro para a lista.
 * @return true se a lista estiver cheia, false caso contrário.
 */
bool lista_seq_ord_sr_cheia(const ListaSeqOrdSR* l);

/**
 * @brief Insere um elemento na lista mantendo a ordem e sem permitir repetições.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (lista cheia ou elemento repetido).
 */
bool lista_seq_ord_sr_inserir(ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento);

/**
 * @brief Remove um elemento da lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser removido.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (elemento não encontrado).
 */
bool lista_seq_ord_sr_remover(ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento, TipoElementoListaOrdSR* removido);

/**
 * @brief Busca um elemento na lista.
 *        Utiliza busca binária devido à ordenação.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser buscado.
 * @param indice Ponteiro para armazenar o índice do elemento encontrado (pode ser NULL).
 * @return true se o elemento foi encontrado, false caso contrário.
 */
bool lista_seq_ord_sr_buscar(const ListaSeqOrdSR* l, TipoElementoListaOrdSR elemento, int* indice);

/**
 * @brief Obtém o tamanho atual (número de elementos) da lista.
 * @param l Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
int lista_seq_ord_sr_tamanho(const ListaSeqOrdSR* l);

/**
 * @brief Imprime os elementos da lista (para fins de depuração).
 * @param l Ponteiro para a lista.
 */
void lista_seq_ord_sr_imprimir(const ListaSeqOrdSR* l);


#endif // LISTA_SEQ_ORD_SR_H