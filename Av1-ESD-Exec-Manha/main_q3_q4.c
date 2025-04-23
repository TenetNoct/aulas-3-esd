#include <stdio.h>
#include <stdlib.h>
#include "lista_dup_enc_circ.h"

// Função auxiliar para preencher uma lista
void preencher_lista(ListaDupEncCirc* l, int elementos[], int n) {
    for (int i = 0; i < n; i++) {
        lista_dup_enc_circ_inserir_fim(l, elementos[i]);
    }
}

int main() {
    printf("--- Questão 3 e 4: TAD Lista Duplamente Encadeada Circular ---\n\n");

    // --- Teste Questão 3: retira_sublista ---
    printf("--- Teste Questão 3: retira_sublista ---\n");

    ListaDupEncCirc* l1 = lista_dup_enc_circ_criar();
    ListaDupEncCirc* l2 = lista_dup_enc_circ_criar();
    ListaDupEncCirc* l3 = lista_dup_enc_circ_criar();
    ListaDupEncCirc* l4 = lista_dup_enc_circ_criar();

    // Exemplo 1: l1 = {1, 2, 3, 4, 5, 6, 7}, l2 = {3, 4, 5}
    int elems1[] = {1, 2, 3, 4, 5, 6, 7};
    int elems2[] = {3, 4, 5};
    preencher_lista(l1, elems1, 7);
    preencher_lista(l2, elems2, 3);

    printf("L1 original: ");
    lista_dup_enc_circ_imprimir(l1);
    printf("L2 (sublista a remover): ");
    lista_dup_enc_circ_imprimir(l2);

    if (lista_dup_enc_circ_retira_sublista(l1, l2)) {
        printf("Sublista L2 encontrada e removida de L1.\n");
    } else {
        printf("Sublista L2 NÃO encontrada em L1.\n");
    }
    printf("L1 após tentativa de remoção: ");
    lista_dup_enc_circ_imprimir(l1);
    printf("\n");

    // Exemplo 2: l3 = {1, 2, 1, 2, 3, 4}, l4 = {1, 2, 3}
    int elems3[] = {1, 2, 1, 2, 3, 4};
    int elems4[] = {1, 2, 3};
    preencher_lista(l3, elems3, 6);
    preencher_lista(l4, elems4, 3);

    printf("L3 original: ");
    lista_dup_enc_circ_imprimir(l3);
    printf("L4 (sublista a remover): ");
    lista_dup_enc_circ_imprimir(l4);

    if (lista_dup_enc_circ_retira_sublista(l3, l4)) {
        printf("Sublista L4 encontrada e removida de L3.\n");
    } else {
        printf("Sublista L4 NÃO encontrada em L3.\n");
    }
    printf("L3 após tentativa de remoção: ");
    lista_dup_enc_circ_imprimir(l3);
    printf("\n");

    // Exemplo 3: l1 (agora {1, 2, 6, 7}), l4 = {1, 2, 3} (não deve encontrar)
    printf("L1 atual: ");
    lista_dup_enc_circ_imprimir(l1);
    printf("L4 (sublista a remover): ");
    lista_dup_enc_circ_imprimir(l4);
    if (lista_dup_enc_circ_retira_sublista(l1, l4)) {
        printf("Sublista L4 encontrada e removida de L1.\n");
    } else {
        printf("Sublista L4 NÃO encontrada em L1.\n");
    }
    printf("L1 após tentativa de remoção: ");
    lista_dup_enc_circ_imprimir(l1);
    printf("\n");

    lista_dup_enc_circ_destruir(&l1);
    lista_dup_enc_circ_destruir(&l2);
    lista_dup_enc_circ_destruir(&l3);
    lista_dup_enc_circ_destruir(&l4);

    // --- Teste Questão 4: Operações básicas da lista ---
    printf("\n--- Teste Questão 4: Operações Básicas ---\n");

    // Criando uma lista (com repetição, não classificada - padrão da implementação)
    printf("1. Criando lista vazia...\n");
    ListaDupEncCirc* lista_teste = lista_dup_enc_circ_criar();
    lista_dup_enc_circ_imprimir(lista_teste);

    // Inserindo elementos
    printf("\n2. Inserindo elementos (10, 20, 5, 20):\n");
    lista_dup_enc_circ_inserir_fim(lista_teste, 10);
    printf("Após inserir 10: ");
    lista_dup_enc_circ_imprimir(lista_teste);
    lista_dup_enc_circ_inserir_fim(lista_teste, 20);
    printf("Após inserir 20: ");
    lista_dup_enc_circ_imprimir(lista_teste);
    lista_dup_enc_circ_inserir_inicio(lista_teste, 5);
    printf("Após inserir 5 no início: ");
    lista_dup_enc_circ_imprimir(lista_teste);
    lista_dup_enc_circ_inserir_posicao(lista_teste, 15, 2);
    printf("Após inserir 15 na posição 2: ");
    lista_dup_enc_circ_imprimir(lista_teste);
    lista_dup_enc_circ_inserir_fim(lista_teste, 20); // Inserindo repetido
    printf("Após inserir 20 (repetido): ");
    lista_dup_enc_circ_imprimir(lista_teste);

    // Removendo elementos
    printf("\n3. Removendo elementos:\n");
    TipoElementoListaDupEncCirc removido;
    if (lista_dup_enc_circ_remover_inicio(lista_teste, &removido)) {
        printf("Removeu do início (%d): ", removido);
        lista_dup_enc_circ_imprimir(lista_teste);
    }
    if (lista_dup_enc_circ_remover_fim(lista_teste, &removido)) {
        printf("Removeu do fim (%d): ", removido);
        lista_dup_enc_circ_imprimir(lista_teste);
    }
    if (lista_dup_enc_circ_remover_posicao(lista_teste, 1, &removido)) {
        printf("Removeu da posição 1 (%d): ", removido);
        lista_dup_enc_circ_imprimir(lista_teste);
    }
    // Tentando remover de posição inválida
    if (!lista_dup_enc_circ_remover_posicao(lista_teste, 5, &removido)) {
        printf("Tentativa de remover da posição 5 (inválida) falhou como esperado.\n");
    }

    // Buscando elemento
    printf("\n4. Buscando elemento 20:\n");
    int indice;
    if (lista_dup_enc_circ_buscar(lista_teste, 20, &indice)) {
        printf("Elemento 20 encontrado na posição %d.\n", indice);
    } else {
        printf("Elemento 20 não encontrado.\n");
    }

    // Obtendo elemento
    printf("\n5. Obtendo elemento da posição 0:\n");
    TipoElementoListaDupEncCirc elemento;
    if (lista_dup_enc_circ_obter_elemento(lista_teste, 0, &elemento)) {
        printf("Elemento na posição 0: %d\n", elemento);
    } else {
        printf("Não foi possível obter elemento da posição 0.\n");
    }

    // Liberando a lista de teste
    printf("\n6. Destruindo a lista de teste...\n");
    lista_dup_enc_circ_destruir(&lista_teste);
    printf("Lista destruída.");
    // Tentar imprimir lista destruída (deve indicar inválida ou erro)
    // lista_dup_enc_circ_imprimir(lista_teste); // Descomentar para testar segurança

    printf("\n\n--- Fim da Questão 3 e 4 ---\n");

    return 0;
}