#ifndef LISTASEQ_H
#define LISTASEQ_H

typedef struct tipo_lista tLista;

/*cria lista vazia*/
tLista * lista_cria_vazia(int maximo,int classif, int repet);
//lista está vazia?
int lista_vazia(const tLista *pl);
//lista está cheia?
int lista_cheia(const tLista *pl);
//lista com repetição?
int lista_repet(const tLista *pl);
//lista classificada?
int lista_classif(const tLista *pl);
//percorre a lista
void lista_percorre(const tLista *pl);
//inclui novo elemento na lista
int lista_inclui(tLista *pl, int novo);
//exclui elemento da lista
int lista_exclui(tLista *pl, int elim);
//atualiza elemento na lista
int lista_atualiza(tLista *pl, int antigo, int novo);
//consulta elemento na lista
int lista_consulta(const tLista *pl, int chave, int *valor);
//redimensiona a lista quando estiver cheia
int lista_redimensiona(tLista *pl, int novo_tamanho);
//libera a memória alocada para a lista
void lista_libera(tLista *pl);

#endif /* LISTASEQ_H */