#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "estante.h"

// Estrutura da estante
typedef struct estante TEstante;

TEstante* criarEstante(){
    TEstante *novoEstante = (TEstante *)malloc(sizeof(TEstante));
    if(novoEstante == NULL){
        return NULL;
    }

    strcpy(novoEstante->nome, "Estante");
    novoEstante->tamanho = 0;

    return novoEstante;
}

void adicionarLivro(TEstante *estante, Tlivro *livro){
    if(estante->tamanho < 20){
        estante->livros[estante->tamanho] = livro;
        estante->tamanho++;
    } else {  
        printf("Estante cheia!\n");
    }
}

void removerLivro(TEstante *estante, int indice){
    if(indice < 0 || indice >= estante->tamanho){
        printf("Indice invalido!\n");
        return;
    }

    for(int i = indice; i < estante->tamanho - 1; i++){
        estante->livros[i] = estante->livros[i + 1];
    }

    estante->tamanho--;
}

void imprimirEstante(TEstante *estante){
    
    printf("Estante: %s\n", estante->nome);
    printf("Livros: %d\n", estante->tamanho);

}

void imprimirLivros(TEstante *estante){
    for(int i = 0; i < estante->tamanho; i++){
        printf("Indíce %d: ", i);
        printf("Livro %d: %s\n", i, estante->livros[i]->nome);
        printf("Autor: %s\n", estante->livros[i]->autor);
        printf("Paginas: %d\n", estante->livros[i]->paginas);
        printf("Ano: %d\n", estante->livros[i]->ano);
        printf("\n");        
    }
}

void liberarEstante(TEstante *estante){
    for(int i = 0; i < estante->tamanho; i++){
        liberarLivro(estante->livros[i]);
    }

    free(estante);
}

void editarLivro(TEstante *estante, int indice, char *novoNome, char *novoAutor, int novasPaginas, int novoAno){
    if(indice < 0 || indice >= estante->tamanho){
        printf("Indice invalido!\n");
        return;
    }

    alterarLivro(estante->livros[indice], novoNome, novoAutor, novasPaginas, novoAno);
}

void editarEstante(TEstante *estante, char *novoNome){
    strcpy(estante->nome, novoNome);
}

void ordenarEstante(TEstante *estante){
    for(int i = 0; i < estante->tamanho - 1; i++){
        for(int j = 0; j < estante->tamanho - i - 1; j++){
            if(strcmp(estante->livros[j]->nome, estante->livros[j + 1]->nome) > 0){
                Tlivro *temp = estante->livros[j];
                estante->livros[j] = estante->livros[j + 1];
                estante->livros[j + 1] = temp; 
            } 
        } 
    }
}

void imprimirLivroEstante(TEstante *estante, int indice){
    imprimirLivro(estante->livros[indice]);
}

void buscarLivro(TEstante *estante, char *nome){
    for(int i = 0; i < estante->tamanho; i++){
        if(strcmp(estante->livros[i]->nome, nome) == 0){
            printf("Livro encontrado!\n");
            printf("Indice: %d\n", i);
            printf("Livro: %s\n", estante->livros[i]->nome); 
        } 
    }
}

void getEstante(TEstante *estante){
    char buffer[100];
    sprintf(buffer, "Estante: %s\n", estante->nome);
    printf("%s", buffer);
    sprintf(buffer, "Livros: %d\n", estante->tamanho);
    printf("%s", buffer);
}

void getLivroEstante(TEstante *estante, int indice){
    getLivro(estante->livros[indice]); 
}

void getNomeEstante(TEstante *estante){
    char buffer[100];
    sprintf(buffer, "Nome da Estante: %s\n", estante->nome);
    printf("%s", buffer);
}

void getAutorEstante(TEstante *estante){
    char buffer[100];
    for(int i = 0; i < estante->tamanho; i++){
        sprintf(buffer, "Autor do livro %d: %s\n", i, estante->livros[i]->autor);
        printf("%s", buffer);
    }
}
