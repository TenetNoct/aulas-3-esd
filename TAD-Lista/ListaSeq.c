// Inclusão dos arquivos de cabeçalho necessários
#include "ListaSeq.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da estrutura da lista sequencial
struct tipo_lista {
    int* vnos;          // Ponteiro para o array de elementos
    int qtnos;          // Quantidade atual de elementos
    int maximo;         // Capacidade máxima da lista
    int ehclassificada; // Flag que indica se a lista é ordenada
    int temrepeticao;   // Flag que indica se permite elementos repetidos
};

// Função que cria uma lista vazia com os parâmetros especificados
tLista * lista_cria_vazia(int maximo, int classif, int repet) {
    tLista *pl = (tLista*) malloc(sizeof(tLista));     // Aloca memória para a estrutura
    pl->vnos = (int*)malloc(sizeof(int) * maximo);     // Aloca memória para o array
    pl->qtnos = 0;                                     // Inicializa com zero elementos
    pl->maximo = maximo;                               // Define o tamanho máximo
    pl->ehclassificada = classif;                      // Define se é classificada
    pl->temrepeticao = repet;                          // Define se permite repetição
    return pl;
}

// Função que verifica se a lista está vazia
int lista_vazia(const tLista *pl) {
    return (pl->qtnos == 0);
}

// Função que verifica se a lista está cheia
int lista_cheia(const tLista *pl) {
    return (pl->qtnos == pl->maximo);
}

// Função que verifica se a lista permite repetição
int lista_repet(const tLista *pl) {
    return (pl->temrepeticao == 1);
}

// Função que verifica se a lista é classificada (ordenada)
int lista_classif(const tLista *pl) {
    return (pl->ehclassificada == 1);
}

// Função que percorre e imprime todos os elementos da lista
void lista_percorre(const tLista *pl) {
    int i;
    for(i = 0; i < pl->qtnos; i++)
        printf("\n%d", pl->vnos[i]);
}

// Função de busca desordenada sem repetição
int busca_des_srep(tLista *pl, int chave, int *pos) {
    int i;
    for(i = 0; (i < pl->qtnos) && (pl->vnos[i] != chave); i++); // Busca sequencial
    (*pos) = i;                                                   // Atualiza a posição encontrada
    return(i < pl->qtnos);                                       // Retorna se encontrou
}

// Função de busca binária para listas ordenadas
int busca_bin(tLista *pl, int chave, int *pos) {
    int inicio = 0, meio, fim = pl->qtnos-1, achou = 0;
    while((inicio <= fim) && (!achou)) {                    // Enquanto houver intervalo de busca
        meio = (inicio + fim) / 2;                          // Calcula o meio
        if(pl->vnos[meio] == chave)                        // Se encontrou
            achou = 1;
        else if(pl->vnos[meio] > chave)                    // Se está na metade inferior
            fim = meio-1;
        else                                               // Se está na metade superior
            inicio = meio+1;
    }
    if(achou)
        (*pos) = meio;
    else
        (*pos) = inicio;
    return achou;
}

// Função que move elementos para a esquerda (remoção)
void chegaparaca(tLista *pl, int pos, int qt) {
    memcpy(pl->vnos + pos, pl->vnos + pos + qt, sizeof(int) * (pl->qtnos - pos - qt));
}

// Função que move elementos para a direita (inserção)
void chegaparalaMC(tLista *pl, int pos) {
    memcpy(pl->vnos + pos + 1, pl->vnos + pos, sizeof(int) * (pl->qtnos - pos));
}

// Função que inclui um novo elemento na lista
int lista_inclui(tLista *pl, int novo) {
    int posNovo, achou;
    if (lista_cheia(pl))                                   // Verifica se há espaço
        return 0;

    if (!lista_classif(pl)) {                             // Se não é classificada
        if (!lista_repet(pl) && busca_des_srep(pl, novo, &posNovo))  // Verifica duplicata
            return -1;
        posNovo = pl->qtnos;                              // Insere no final
    } else {                                              // Se é classificada
        achou = busca_bin(pl, novo, &posNovo);           // Busca posição correta
        if (achou && !lista_repet(pl))                    // Verifica duplicata
            return -1;
        chegaparalaMC(pl, posNovo);                       // Abre espaço
    }
    pl->vnos[posNovo] = novo;                            // Insere o elemento
    pl->qtnos++;                                         // Incrementa contador
    return 1;
}

// Função que exclui um elemento da lista
int lista_exclui(tLista *pl, int no) {
    int posRet, achou, qt;
    if (lista_vazia(pl))                                 // Verifica se está vazia
        return 0;

    if (lista_repet(pl) && !lista_classif(pl))          // Caso especial
        return 1;

    if(lista_classif(pl))                               // Busca elemento
        achou = busca_bin(pl, no, &posRet);
    else
        achou = busca_des_srep(pl, no, &posRet);

    if (!achou)                                         // Se não encontrou
        return -1;

    if (lista_repet(pl)) {                             // Se permite repetição
        qt = 1;
        int inic = posRet, fim = posRet;
        while (inic >= 0 && pl->vnos[inic] == no) {    // Conta repetições anteriores
            qt++;
            inic--;
        }
        while (fim < pl->qtnos && pl->vnos[fim] == no) { // Conta repetições posteriores
            qt++;
            fim++;
        }
        posRet = inic;
    } else {
        qt = 1;
    }
    chegaparaca(pl, posRet, qt);                       // Remove elemento(s)
    pl->qtnos -= qt;                                   // Atualiza contador
    return 1;
}

// Função que atualiza um elemento na lista
int lista_atualiza(tLista *pl, int antigo, int novo) {
    int posAntigo, posNovo, achou;
    
    if (lista_vazia(pl))                               // Verifica se está vazia
        return 0;
    
    if (lista_classif(pl))                            // Busca elemento antigo
        achou = busca_bin(pl, antigo, &posAntigo);
    else
        achou = busca_des_srep(pl, antigo, &posAntigo);
    
    if (!achou)                                       // Se não encontrou
        return -1;
    
    if (!lista_repet(pl)) {                          // Verifica duplicata do novo
        if (lista_classif(pl))
            achou = busca_bin(pl, novo, &posNovo);
        else
            achou = busca_des_srep(pl, novo, &posNovo);
        
        if (achou)
            return -2;
    }
    
    pl->vnos[posAntigo] = novo;                      // Atualiza o elemento
    
    if (lista_classif(pl)) {                         // Reordena se necessário
        chegaparaca(pl, posAntigo, 1);
        pl->qtnos--;
        lista_inclui(pl, novo);
    }
    
    return 1;
}

// Função que consulta um elemento na lista
int lista_consulta(const tLista *pl, int chave, int *valor) {
    int pos, achou;
    
    if (lista_vazia(pl))                             // Verifica se está vazia
        return 0;
    
    if (lista_classif(pl))                          // Busca o elemento
        achou = busca_bin((tLista*)pl, chave, &pos);
    else
        achou = busca_des_srep((tLista*)pl, chave, &pos);
    
    if (!achou)                                     // Se não encontrou
        return -1;
    
    *valor = pl->vnos[pos];                        // Retorna o valor
    return 1;
}

// Função que redimensiona a lista
int lista_redimensiona(tLista *pl, int novo_tamanho) {
    if (novo_tamanho < pl->qtnos)                  // Verifica se o novo tamanho é válido
        return 0;
    
    int *novo_vetor = (int*)realloc(pl->vnos, sizeof(int) * novo_tamanho);  // Realoca memória
    if (novo_vetor == NULL)                        // Verifica se alocação falhou
        return 0;
    
    pl->vnos = novo_vetor;                        // Atualiza ponteiro
    pl->maximo = novo_tamanho;                    // Atualiza tamanho máximo
    return 1;
}

// Função que libera a memória alocada para a lista
void lista_libera(tLista *pl) {
    if (pl != NULL) {                             // Verifica se a lista existe
        if (pl->vnos != NULL)                     // Libera array de elementos
            free(pl->vnos);
        free(pl);                                 // Libera estrutura da lista
    }
}