#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

// Remove this line since the typedef is now in the header
// typedef struct livro Tlivro;

Tlivro* criarLivro(char *nome, char *autor, int paginas, int ano){
    Tlivro *novoLivro = (Tlivro *)malloc(sizeof(Tlivro));
    if(novoLivro == NULL){
        return NULL;
    }

    strcpy(novoLivro->nome, nome);
    strcpy(novoLivro->autor, autor);
    novoLivro->paginas = paginas;
    novoLivro->ano = ano;

    return novoLivro;
}

void imprimirLivro(Tlivro *livro){

    printf("Nome: %s\n", livro->nome);
    printf("Autor: %s\n", livro->autor);
    printf("Paginas: %d\n", livro->paginas);
    printf("Ano: %d\n", livro->ano);

}

void liberarLivro(Tlivro *livro){
    free(livro);
}

void alterarLivro(Tlivro *livro, char *novoNome, char *novoAutor, int novasPaginas, int novoAno){
    
    strcpy(livro->nome, novoNome);
    strcpy(livro->autor, novoAutor);
    livro->paginas = novasPaginas;
    livro->ano = novoAno;

}

char* getNomeLivro(Tlivro *livro){
    return livro->nome;
}

char* getAutorLivro(Tlivro *livro){
    return livro->autor;
}

char* getLivro(Tlivro *livro){
    char *livroStr = (char *)malloc(100 * sizeof(char)); 
    sprintf(livroStr, "Nome: %s\nAutor: %s\nPaginas: %d\nAno: %d\n", livro->nome, livro->autor, livro->paginas, livro->ano);

    return livroStr;
}