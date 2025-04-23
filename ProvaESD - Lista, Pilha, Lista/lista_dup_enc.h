#ifndef LISTA_DUP_ENC_H
#define LISTA_DUP_ENC_H

#include <stdbool.h>

// Define o tipo do dado armazenado na lista (pode ser alterado)
typedef int TipoElementoListaDupEnc;

// --- Estrutura do Nó ---
typedef struct NoListaDupEnc {
    TipoElementoListaDupEnc dado;
    struct NoListaDupEnc* proximo;
    struct NoListaDupEnc* anterior;
} NoListaDupEnc;

// --- Estrutura da Lista Duplamente Encadeada ---
typedef struct {
    NoListaDupEnc* inicio; // Ponteiro para o primeiro nó
    NoListaDupEnc* fim;    // Ponteiro para o último nó
    int tamanho;           // Número de elementos na lista
} ListaDupEnc;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova lista duplamente encadeada vazia.
 * @return Ponteiro para a lista criada ou NULL em caso de erro de alocação.
 */
ListaDupEnc* lista_dup_enc_criar();

/**
 * @brief Destroi a lista, liberando toda a memória alocada (nós e a estrutura da lista).
 * @param l Ponteiro para o ponteiro da lista.
 */
void lista_dup_enc_destruir(ListaDupEnc** l);

/**
 * @brief Verifica se a lista está vazia.
 * @param l Ponteiro para a lista.
 * @return true se a lista estiver vazia, false caso contrário.
 */
bool lista_dup_enc_vazia(const ListaDupEnc* l);

/**
 * @brief Insere um elemento no início da lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_dup_enc_inserir_inicio(ListaDupEnc* l, TipoElementoListaDupEnc elemento);

/**
 * @brief Insere um elemento no final da lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_dup_enc_inserir_fim(ListaDupEnc* l, TipoElementoListaDupEnc elemento);

/**
 * @brief Insere um elemento em uma posição específica da lista (baseado em índice 0).
 *        A inserção desloca os elementos a partir da posição.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @param posicao O índice onde o elemento deve ser inserido (0 para início, tamanho para fim).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou erro de alocação).
 */
bool lista_dup_enc_inserir_posicao(ListaDupEnc* l, TipoElementoListaDupEnc elemento, int posicao);

/**
 * @brief Remove o elemento do início da lista.
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_dup_enc_remover_inicio(ListaDupEnc* l, TipoElementoListaDupEnc* removido);

/**
 * @brief Remove o elemento do final da lista.
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_dup_enc_remover_fim(ListaDupEnc* l, TipoElementoListaDupEnc* removido);

/**
 * @brief Remove o elemento de uma posição específica da lista (baseado em índice 0).
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento a ser removido.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou lista vazia).
 */
bool lista_dup_enc_remover_posicao(ListaDupEnc* l, int posicao, TipoElementoListaDupEnc* removido);

/**
 * @brief Busca um elemento na lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser buscado.
 * @param indice Ponteiro para armazenar o índice da primeira ocorrência do elemento (pode ser NULL).
 * @return true se o elemento foi encontrado, false caso contrário.
 */
bool lista_dup_enc_buscar(const ListaDupEnc* l, TipoElementoListaDupEnc elemento, int* indice);

/**
 * @brief Obtém o elemento em uma posição específica da lista.
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento desejado.
 * @param elemento Ponteiro para armazenar o elemento encontrado.
 * @return true se a posição for válida, false caso contrário.
 */
bool lista_dup_enc_obter_elemento(const ListaDupEnc* l, int posicao, TipoElementoListaDupEnc* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da lista.
 * @param l Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
int lista_dup_enc_tamanho(const ListaDupEnc* l);

/**
 * @brief Imprime os elementos da lista do início para o fim (para fins de depuração).
 * @param l Ponteiro para a lista.
 */
void lista_dup_enc_imprimir_frente(const ListaDupEnc* l);

/**
 * @brief Imprime os elementos da lista do fim para o início (para fins de depuração).
 * @param l Ponteiro para a lista.
 */
void lista_dup_enc_imprimir_tras(const ListaDupEnc* l);


#endif // LISTA_DUP_ENC_H