#ifndef DATA_H
#define DATA_H

typedef struct data tData;

tData* dta_cria(int dia, int mes, int ano);
void dta_libera(tData* p);
void dta_acessa(tData* p, int* dia, int* mes, int* ano);
void dta_atribui(tData* p, int dia, int mes, int ano);
tData* dta_intervalo(tData* p1, int X);
tData* dta_exibe(tData* p1);
char* dta_getData(tData* p);
int dta_maiorIgual(tData* p1, tData* p2);
char* dta_MesExtenso(tData* p);

#endif