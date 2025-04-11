#ifndef FILASEQ_H
#define FILASEQ_H

typedef struct tipo_fila tFila;

/*cria fila vazia*/
tFila * fila_cria_vazia(int maximo);
//fila está vazia?
int fila_vazia(const tFila *pf);
//fila está cheia?
int fila_cheia(const tFila *pf);
//percorre a fila (do início para o fim)
void fila_percorre(const tFila *pf);
//enfileira novo elemento (enqueue)
int fila_enqueue(tFila *pf, int novo);
//desenfileira elemento (dequeue)
int fila_dequeue(tFila *pf, int *valor);
//consulta elemento no início da fila
int fila_consulta_inicio(const tFila *pf, int *valor);
//redimensiona a fila quando estiver cheia
int fila_redimensiona(tFila *pf, int novo_tamanho);
//libera a memória alocada para a fila
void fila_libera(tFila *pf);

#endif /* FILASEQ_H */