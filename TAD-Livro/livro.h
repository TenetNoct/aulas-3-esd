#ifndef LIVRO_H
#define LIVRO_H

typedef struct livro {
    char nome[100];
    char autor[100];
    int paginas;
    int ano;
} Tlivro;

Tlivro* criarLivro(char *nome, char *autor, int paginas, int ano);
void imprimirLivro(Tlivro *livro);
void liberarLivro(Tlivro *livro);
void alterarLivro(Tlivro *livro, char *novoNome, char *novoAutor, int novasPaginas, int novoAno);
char* getNomeLivro(Tlivro *livro);
char* getAutorLivro(Tlivro *livro);
char* getLivro(Tlivro *livro);

#endif /* LIVRO_H */