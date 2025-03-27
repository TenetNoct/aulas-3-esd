#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compromisso.h"

Compromisso *criarCompromisso(int dia, int mes, int ano, int hora, int minuto, char *descricao) {
    Timestamp *timestamp = criarTimestamp(dia, mes, ano, hora, minuto);
    if (timestamp == NULL) {
        return NULL; // Timestamp inválido
    }
    
    Compromisso *novoCompromisso = (Compromisso *)malloc(sizeof(Compromisso));
    if (novoCompromisso == NULL) {
        destruirTimestamp(timestamp);
        return NULL; // Falha na alocação de memória
    }
    
    novoCompromisso->timestamp = timestamp;
    strncpy(novoCompromisso->descricao, descricao, sizeof(novoCompromisso->descricao) - 1);
    novoCompromisso->descricao[sizeof(novoCompromisso->descricao) - 1] = '\0'; // Garante terminação
    
    return novoCompromisso;
}

void imprimirCompromisso(void *dado) {
    Compromisso *compromisso = (Compromisso *)dado;
    if (compromisso != NULL) {
        printf("Compromisso: ");
        imprimirTimestamp(compromisso->timestamp);
        printf(" - %s\n", compromisso->descricao);
    }
}

void destruirCompromisso(Compromisso *compromisso) {
    if (compromisso != NULL) {
        destruirTimestamp(compromisso->timestamp);
        free(compromisso);
    }
}

void adiarCompromisso(Compromisso *compromisso, int minutos) {
    if (compromisso != NULL && minutos > 0) {
        somarMinutosTimestamp(compromisso->timestamp, minutos);
    }
}

void anteciparCompromisso(Compromisso *compromisso, int minutos) {
    if (compromisso != NULL && minutos > 0) {
        subtrairMinutosTimestamp(compromisso->timestamp, minutos);
    }
}