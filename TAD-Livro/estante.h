#define estante_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

struct estante {
    char nome[50];
    Tlivro *livros[20];
    int tamanho;
};

typedef struct estante TEstante;

TEstante* criarEstante();
void adicionarLivro(TEstante *estante, Tlivro *livro);
void removerLivro(TEstante *estante, int indice);
void imprimirEstante(TEstante *estante);
void imprimirLivros(TEstante *estante);
void liberarEstante(TEstante *estante);
void editarLivro(TEstante *estante, int indice, char *novoNome, char *novoAutor, int novasPaginas, int novoAno);
void editarEstante(TEstante *estante, char *novoNome);
void ordenarEstante(TEstante *estante);
void imprimirLivroEstante(TEstante *estante, int indice);
void buscarLivro(TEstante *estante, char *nome);
void getEstante(TEstante *estante);
void getLivroEstante(TEstante *estante, int indice);
void getNomeEstante(TEstante *estante);
void getAutorEstante(TEstante *estante);
