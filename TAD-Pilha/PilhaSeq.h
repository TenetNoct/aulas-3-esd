#ifndef PILHASEQ_H
#define PILHASEQ_H

typedef struct tipo_pilha tPilha;

/*cria pilha vazia*/
tPilha * pilha_cria_vazia(int maximo);
//pilha está vazia?
int pilha_vazia(const tPilha *pp);
//pilha está cheia?
int pilha_cheia(const tPilha *pp);
//percorre a pilha (do topo para a base)
void pilha_percorre(const tPilha *pp);
//empilha novo elemento (push)
int pilha_push(tPilha *pp, int novo);
//desempilha elemento (pop)
int pilha_pop(tPilha *pp, int *valor);
//consulta elemento no topo da pilha
int pilha_consulta_topo(const tPilha *pp, int *valor);
//redimensiona a pilha quando estiver cheia
int pilha_redimensiona(tPilha *pp, int novo_tamanho);
//libera a memória alocada para a pilha
void pilha_libera(tPilha *pp);

#endif /* PILHASEQ_H */