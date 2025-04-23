#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    int dia, mes, ano;
};

tData* dta_cria(int dia, int mes, int ano) {
    tData* p = (tData*)malloc(sizeof(tData));
    if (p != NULL) {
        p->dia = dia;
        p->mes = mes;
        p->ano = ano;
    }
    return p;
}

void dta_libera(tData* p) {
    free(p);
}

void dta_acessa(tData* p, int* dia, int* mes, int* ano) {
    *dia = p->dia;
    *mes = p->mes;
    *ano = p->ano;
}

void dta_atribui(tData* p, int dia, int mes, int ano) {
    p->dia = dia;
    p->mes = mes;
    p->ano = ano;
}

tData* dta_intervalo(tData* p1, int X) {
    // Simplified implementation, doesn't handle month/year changes
    tData* newDate = dta_cria(p1->dia, p1->mes, p1->ano);
    newDate->dia += X;
    return newDate;
}

tData* dta_exibe(tData* p1) {
    printf("%02d/%02d/%04d", p1->dia, p1->mes, p1->ano);
    return p1;
}

char* dta_getData(tData* p) {
    char* dateStr = (char*)malloc(11 * sizeof(char));
    sprintf(dateStr, "%02d/%02d/%04d", p->dia, p->mes, p->ano);
    return dateStr;
}

int dta_maiorIgual(tData* p1, tData* p2) {
    if (p1->ano > p2->ano) return 1;
    if (p1->ano < p2->ano) return 0;
    if (p1->mes > p2->mes) return 1;
    if (p1->mes < p2->mes) return 0;
    return p1->dia >= p2->dia;
}

char* dta_MesExtenso(tData* p) {
    char* meses[] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    char* mesExtenso = (char*)malloc(20 * sizeof(char));
    strcpy(mesExtenso, meses[p->mes - 1]);
    return mesExtenso;
}