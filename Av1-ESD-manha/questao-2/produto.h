#ifndef PRODUTO_H
#define PRODUTO_H

#include "data.h"

typedef struct tProd tProduto;

tProduto* prod_cria(char* id, char* codBarras, int dia, int mes, int ano, int val, float pr);
void prod_Exibir(tProduto* p);
int prod_estaNaValidade(tProduto* p, tData* dta);
int prod_ehSemelhante(tProduto* p1, tProduto* p2);
void prod_reajusta(tProduto* p, float perc);
char* prod_get_Id(tProduto* p);

#endif