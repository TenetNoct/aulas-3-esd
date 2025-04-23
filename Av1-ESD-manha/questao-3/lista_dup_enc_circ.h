#ifndef LISTA_DUP_ENC_CIRC_H
#define LISTA_DUP_ENC_CIRC_H

#include <stdbool.h>

// Define o tipo do dado armazenado na lista (pode ser alterado)
typedef int TipoElementoListaDupEncCirc;

// --- Estrutura do Nó ---
typedef struct NoListaDupEncCirc {
    TipoElementoListaDupEncCirc dado;
    struct NoListaDupEncCirc* proximo;
    struct NoListaDupEncCirc* anterior;
} NoListaDupEncCirc;

// --- Estrutura da Lista Duplamente Encadeada Circular ---
// Usamos um nó sentinela (cabeça) para simplificar operações
typedef struct {
    NoListaDupEncCirc* cabeca; // Nó sentinela (não contém dado útil)
    int tamanho;              // Número de elementos na lista
} ListaDupEncCirc;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova lista duplamente encadeada circular vazia.
 *        Utiliza um nó sentinela.
 * @return Ponteiro para a lista criada ou NULL em caso de erro de alocação.
 */
ListaDupEncCirc* lista_dup_enc_circ_criar();

/**
 * @brief Destroi a lista, liberando toda a memória alocada (nós e a estrutura da lista).
 * @param l Ponteiro para o ponteiro da lista.
 */
void lista_dup_enc_circ_destruir(ListaDupEncCirc** l);

/**
 * @brief Verifica se a lista está vazia.
 * @param l Ponteiro para a lista.
 * @return true se a lista estiver vazia, false caso contrário.
 */
bool lista_dup_enc_circ_vazia(const ListaDupEncCirc* l);

/**
 * @brief Insere um elemento após o nó sentinela (início lógico).
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_dup_enc_circ_inserir_inicio(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento);

/**
 * @brief Insere um elemento antes do nó sentinela (fim lógico).
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_dup_enc_circ_inserir_fim(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento);

/**
 * @brief Insere um elemento em uma posição específica da lista (baseado em índice 0).
 *        A inserção desloca os elementos a partir da posição.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @param posicao O índice onde o elemento deve ser inserido (0 para início, tamanho para fim).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou erro de alocação).
 */
bool lista_dup_enc_circ_inserir_posicao(ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int posicao);

/**
 * @brief Remove o elemento após o nó sentinela (início lógico).
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_dup_enc_circ_remover_inicio(ListaDupEncCirc* l, TipoElementoListaDupEncCirc* removido);

/**
 * @brief Remove o elemento antes do nó sentinela (fim lógico).
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_dup_enc_circ_remover_fim(ListaDupEncCirc* l, TipoElementoListaDupEncCirc* removido);

/**
 * @brief Remove o elemento de uma posição específica da lista (baseado em índice 0).
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento a ser removido.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou lista vazia).
 */
bool lista_dup_enc_circ_remover_posicao(ListaDupEncCirc* l, int posicao, TipoElementoListaDupEncCirc* removido);

/**
 * @brief Busca um elemento na lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser buscado.
 * @param indice Ponteiro para armazenar o índice da primeira ocorrência do elemento (pode ser NULL).
 * @return true se o elemento foi encontrado, false caso contrário.
 */
bool lista_dup_enc_circ_buscar(const ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int* indice);

/**
 * @brief Obtém o elemento em uma posição específica da lista.
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento desejado.
 * @param elemento Ponteiro para armazenar o elemento encontrado.
 * @return true se a posição for válida, false caso contrário.
 */
bool lista_dup_enc_circ_obter_elemento(const ListaDupEncCirc* l, int posicao, TipoElementoListaDupEncCirc* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da lista.
 * @param l Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
int lista_dup_enc_circ_tamanho(const ListaDupEncCirc* l);

/**
 * @brief Imprime os elementos da lista a partir do início lógico (para fins de depuração).
 * @param l Ponteiro para a lista.
 */
void lista_dup_enc_circ_imprimir(const ListaDupEncCirc* l);


/**
 * @brief Copia uma sublista de n nós que antecedem um elemento específico.
 * @param l Ponteiro para a lista original.
 * @param elemento O elemento a partir do qual a sublista será copiada.
 * @param n O número de nós a serem copiados.
 * @return Ponteiro para a nova lista contendo a sublista copiada ou NULL se a operação falhar.
 */
ListaDupEncCirc* lista_dup_enc_circ_copia_sublista(const ListaDupEncCirc* l, TipoElementoListaDupEncCirc elemento, int n);

#endif // LISTA_DUP_ENC_CIRC_H