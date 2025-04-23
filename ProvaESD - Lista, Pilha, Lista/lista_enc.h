#ifndef LISTA_ENC_H
#define LISTA_ENC_H

#include <stdbool.h>

// Define o tipo do dado armazenado na lista (pode ser alterado)
typedef int TipoElementoListaEnc;

// --- Estrutura do Nó ---
typedef struct NoListaEnc {
    TipoElementoListaEnc dado;
    struct NoListaEnc* proximo;
} NoListaEnc;

// --- Estrutura da Lista Encadeada ---
typedef struct {
    NoListaEnc* inicio; // Ponteiro para o primeiro nó da lista
    int tamanho;        // Número de elementos na lista
} ListaEnc;

// --- Funções Essenciais ---

/**
 * @brief Cria uma nova lista encadeada vazia.
 * @return Ponteiro para a lista criada ou NULL em caso de erro de alocação.
 */
ListaEnc* lista_enc_criar();

/**
 * @brief Destroi a lista, liberando toda a memória alocada (nós e a estrutura da lista).
 * @param l Ponteiro para o ponteiro da lista.
 */
void lista_enc_destruir(ListaEnc** l);

/**
 * @brief Verifica se a lista está vazia.
 * @param l Ponteiro para a lista.
 * @return true se a lista estiver vazia, false caso contrário.
 */
bool lista_enc_vazia(const ListaEnc* l);

/**
 * @brief Insere um elemento no início da lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_enc_inserir_inicio(ListaEnc* l, TipoElementoListaEnc elemento);

/**
 * @brief Insere um elemento no final da lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @return true se a operação foi bem-sucedida, false caso contrário (erro de alocação).
 */
bool lista_enc_inserir_fim(ListaEnc* l, TipoElementoListaEnc elemento);

/**
 * @brief Insere um elemento em uma posição específica da lista (baseado em índice 0).
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser inserido.
 * @param posicao O índice onde o elemento deve ser inserido (0 para início, tamanho para fim).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou erro de alocação).
 */
bool lista_enc_inserir_posicao(ListaEnc* l, TipoElementoListaEnc elemento, int posicao);

/**
 * @brief Remove o elemento do início da lista.
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_enc_remover_inicio(ListaEnc* l, TipoElementoListaEnc* removido);

/**
 * @brief Remove o elemento do final da lista.
 * @param l Ponteiro para a lista.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (lista vazia).
 */
bool lista_enc_remover_fim(ListaEnc* l, TipoElementoListaEnc* removido);

/**
 * @brief Remove o elemento de uma posição específica da lista (baseado em índice 0).
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento a ser removido.
 * @param removido Ponteiro para armazenar o elemento removido (pode ser NULL).
 * @return true se a operação foi bem-sucedida, false caso contrário (posição inválida ou lista vazia).
 */
bool lista_enc_remover_posicao(ListaEnc* l, int posicao, TipoElementoListaEnc* removido);

/**
 * @brief Busca um elemento na lista.
 * @param l Ponteiro para a lista.
 * @param elemento O elemento a ser buscado.
 * @param indice Ponteiro para armazenar o índice da primeira ocorrência do elemento (pode ser NULL).
 * @return true se o elemento foi encontrado, false caso contrário.
 */
bool lista_enc_buscar(const ListaEnc* l, TipoElementoListaEnc elemento, int* indice);

/**
 * @brief Obtém o elemento em uma posição específica da lista.
 * @param l Ponteiro para a lista.
 * @param posicao O índice do elemento desejado.
 * @param elemento Ponteiro para armazenar o elemento encontrado.
 * @return true se a posição for válida, false caso contrário.
 */
bool lista_enc_obter_elemento(const ListaEnc* l, int posicao, TipoElementoListaEnc* elemento);

/**
 * @brief Obtém o tamanho atual (número de elementos) da lista.
 * @param l Ponteiro para a lista.
 * @return O número de elementos na lista.
 */
int lista_enc_tamanho(const ListaEnc* l);

/**
 * @brief Imprime os elementos da lista (para fins de depuração).
 * @param l Ponteiro para a lista.
 */
void lista_enc_imprimir(const ListaEnc* l);

#endif // LISTA_ENC_H