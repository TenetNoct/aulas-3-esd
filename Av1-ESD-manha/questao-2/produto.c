#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tProd {
    char* nome;
    char* codBarras;
    tData* dtaFabricacao;
    int diasValidade;
    float preco;
};

tProduto* prod_cria(char* id, char* codBarras, int dia, int mes, int ano, int val, float pr) {
    tProduto* p = (tProduto*)malloc(sizeof(tProduto));
    if (p != NULL) {
        p->nome = (char*)malloc((strlen(id) + 1) * sizeof(char));
        strcpy(p->nome, id);
        p->codBarras = (char*)malloc((strlen(codBarras) + 1) * sizeof(char));
        strcpy(p->codBarras, codBarras);
        p->dtaFabricacao = dta_cria(dia, mes, ano);
        p->diasValidade = val;
        p->preco = pr;
    }
    return p;
}

void prod_Exibir(tProduto* p) {
    printf("Nome: %s\n", p->nome);
    printf("Código de Barras: %s\n", p->codBarras);
    printf("Data de Fabricação: ");
    dta_exibe(p->dtaFabricacao);
    printf("\nDias de Validade: %d\n", p->diasValidade);
    printf("Preço: %.2f\n", p->preco);
}

int prod_estaNaValidade(tProduto* p, tData* dta) {
    tData* dtaValidade = dta_intervalo(p->dtaFabricacao, p->diasValidade);
    int result = dta_maiorIgual(dta, dtaValidade);
    dta_libera(dtaValidade);
    return !result;
}

int prod_ehSemelhante(tProduto* p1, tProduto* p2) {
    return strcmp(p1->codBarras, p2->codBarras) == 0;
}

void prod_reajusta(tProduto* p, float perc) {
    p->preco += p->preco * (perc / 100);
}

char* prod_get_Id(tProduto* p) {
    return p->nome;
}