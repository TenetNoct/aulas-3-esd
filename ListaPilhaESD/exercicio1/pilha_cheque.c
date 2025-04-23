#include "pilha_cheque.h" // Inclui o arquivo de cabeçalho correspondente que define a estrutura Cheque e as assinaturas das funções
#include <stdlib.h>        // Inclui a biblioteca padrão para funções de alocação de memória (malloc, free)
#include <stdio.h>         // Inclui a biblioteca padrão para funções de entrada/saída (printf, fprintf, perror)

// Estrutura interna da Pilha Sequencial (não visível fora deste arquivo)
// Define como a pilha de cheques é organizada na memória.
struct pilha_sequencial {
    TipoElementoPilha* dados; // Ponteiro para a área de memória (array) onde os cheques (TipoElementoPilha) serão armazenados.
    int topo_idx;             // Índice do array que indica a posição do último cheque inserido (o topo da pilha). -1 significa pilha vazia.
    int capacidade;           // Número máximo de cheques que a pilha pode armazenar atualmente.
};

// --- Implementação das Funções ---

// Função para criar uma nova pilha de cheques
PilhaCheque* pilha_cheque_criar(int capacidade) {
    // Verifica se a capacidade solicitada é válida (maior que zero)
    if (capacidade <= 0) {
        // Imprime uma mensagem de erro no stream de erro padrão
        fprintf(stderr, "Erro: Capacidade da pilha deve ser positiva.\n");
        // Retorna NULL para indicar que a criação falhou
        return NULL;
    }
    // Aloca memória para a estrutura administrativa da pilha (PilhaCheque)
    PilhaCheque* p = (PilhaCheque*)malloc(sizeof(PilhaCheque));
    // Verifica se a alocação da estrutura foi bem-sucedida
    if (!p) {
        // Imprime uma mensagem de erro do sistema (relacionada à falha de memória)
        perror("Erro ao alocar memória para a pilha");
        // Retorna NULL indicando falha
        return NULL;
    }
    // Aloca memória para o array que armazenará os cheques
    // O tamanho é a capacidade desejada multiplicada pelo tamanho de um Cheque (TipoElementoPilha)
    p->dados = (TipoElementoPilha*)malloc(capacidade * sizeof(TipoElementoPilha));
    // Verifica se a alocação do array de dados foi bem-sucedida
    if (!p->dados) {
        // Imprime uma mensagem de erro do sistema
        perror("Erro ao alocar memória para os dados da pilha");
        // Libera a memória alocada para a estrutura da pilha, já que a criação falhou
        free(p);
        // Retorna NULL indicando falha
        return NULL;
    }
    // Armazena a capacidade máxima da pilha
    p->capacidade = capacidade;
    // Inicializa o índice do topo como -1, indicando que a pilha começa vazia
    p->topo_idx = -1; 
    // Retorna o ponteiro para a pilha recém-criada e inicializada
    return p;
}

// Função para destruir uma pilha de cheques e liberar a memória
void pilha_cheque_destruir(PilhaCheque** p) {
    // Verifica se o ponteiro para o ponteiro da pilha é válido e se a pilha que ele aponta existe
    if (p && *p) {
        // Libera a memória alocada para o array de dados (os cheques)
        free((*p)->dados);
        // Libera a memória alocada para a estrutura administrativa da pilha
        free(*p);
        // Define o ponteiro original (fora da função) como NULL para evitar acesso inválido posterior
        *p = NULL;
    }
}

// Função para verificar se a pilha de cheques está vazia
bool pilha_cheque_vazia(const PilhaCheque* p) {
    // Se o ponteiro para a pilha for NULL (inválido), considera-a vazia por segurança
    if (!p) return true;
    // A pilha está vazia se o índice do topo for -1
    return p->topo_idx == -1;
}

// Função para verificar se a pilha de cheques está cheia
bool pilha_cheque_cheia(const PilhaCheque* p) {
    // Se o ponteiro para a pilha for NULL, não pode estar cheia
    if (!p) return false;
    // A pilha está cheia se o índice do topo for igual à capacidade - 1 (última posição do array)
    return p->topo_idx == p->capacidade - 1;
}

// Função para empilhar (adicionar) um cheque no topo da pilha
bool pilha_cheque_empilhar(PilhaCheque* p, TipoElementoPilha elemento) {
    // Verifica se a pilha é válida e se não está cheia
    if (!p || pilha_cheque_cheia(p)) {
        // Imprime uma mensagem de erro se a pilha estiver cheia ou for inválida
        fprintf(stderr, "Erro: Pilha cheia ou inválida para empilhar.\n");
        // OBS: Em implementações mais robustas, poderia tentar redimensionar a pilha aqui.
        // Retorna false indicando que a operação falhou
        return false;
    }
    // Incrementa o índice do topo para apontar para a próxima posição livre
    p->topo_idx++;
    // Copia o cheque 'elemento' para a posição do topo no array de dados
    p->dados[p->topo_idx] = elemento;
    // Retorna true indicando que o empilhamento foi bem-sucedido
    return true;
}

// Função para desempilhar (remover) um cheque do topo da pilha
bool pilha_cheque_desempilhar(PilhaCheque* p, TipoElementoPilha* elemento) {
    // Verifica se a pilha é válida e se não está vazia
    if (!p || pilha_cheque_vazia(p)) {
        // Imprime uma mensagem de erro se a pilha estiver vazia ou for inválida
        fprintf(stderr, "Erro: Pilha vazia ou inválida para desempilhar.\n");
        // Retorna false indicando que a operação falhou
        return false;
    }
    // Se o ponteiro 'elemento' for válido (não NULL), copia o cheque do topo para ele
    if (elemento) {
        *elemento = p->dados[p->topo_idx];
    }
    // Decrementa o índice do topo, efetivamente removendo o elemento (ele será sobrescrito na próxima inserção)
    p->topo_idx--;
    // Retorna true indicando que o desempilhamento foi bem-sucedido
    return true;
}

// Função para consultar o cheque no topo da pilha sem removê-lo
bool pilha_cheque_topo(const PilhaCheque* p, TipoElementoPilha* elemento) {
    // Verifica se a pilha é válida e se não está vazia
    if (!p || pilha_cheque_vazia(p)) {
        // Imprime uma mensagem de erro se a pilha estiver vazia ou for inválida
        fprintf(stderr, "Erro: Pilha vazia ou inválida para consultar topo.\n");
        // Retorna false indicando que a operação falhou
        return false;
    }
    // Se o ponteiro 'elemento' for válido (não NULL), copia o cheque do topo para ele
    if (elemento) {
        *elemento = p->dados[p->topo_idx];
    }
    // Retorna true indicando que a consulta foi bem-sucedida
    return true;
}

// Função para retornar o número de cheques atualmente na pilha
int pilha_cheque_tamanho(const PilhaCheque* p) {
    // Se o ponteiro para a pilha for NULL, o tamanho é 0
    if (!p) return 0;
    // O tamanho é o índice do topo + 1 (porque o índice começa em 0)
    return p->topo_idx + 1;
}