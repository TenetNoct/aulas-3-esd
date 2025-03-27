#include <stdio.h>
#include <stdlib.h>
#include "timestamp.h"

Timestamp *criarTimestamp(int dia, int mes, int ano, int hora, int minuto) {
    Data *data = criarData(dia, mes, ano);
    if (data == NULL) {
        return NULL; // Data inválida
    }
    
    Horario *horario = criarHorario(hora, minuto);
    if (horario == NULL) {
        destruirData(data);
        return NULL; // Horário inválido
    }
    
    Timestamp *novoTimestamp = (Timestamp *)malloc(sizeof(Timestamp));
    if (novoTimestamp == NULL) {
        destruirData(data);
        destruirHorario(horario);
        return NULL; // Falha na alocação de memória
    }
    
    novoTimestamp->data = data;
    novoTimestamp->horario = horario;
    
    return novoTimestamp;
}

void imprimirTimestamp(Timestamp *timestamp) {
    if (timestamp != NULL) {
        imprimirData(timestamp->data);
        printf(" ");
        imprimirHorario(timestamp->horario);
    }
}

void destruirTimestamp(Timestamp *timestamp) {
    if (timestamp != NULL) {
        destruirData(timestamp->data);
        destruirHorario(timestamp->horario);
        free(timestamp);
    }
}

void somarMinutosTimestamp(Timestamp *timestamp, int minutos) {
    if (timestamp == NULL || minutos < 0) {
        return;
    }
    
    int diasAdicionados = somarMinutos(timestamp->horario, minutos);
    if (diasAdicionados > 0) {
        somarDias(timestamp->data, diasAdicionados);
    }
}

void subtrairMinutosTimestamp(Timestamp *timestamp, int minutos) {
    if (timestamp == NULL || minutos < 0) {
        return;
    }
    
    int diasSubtraidos = subtrairMinutos(timestamp->horario, minutos);
    if (diasSubtraidos > 0) {
        subtrairDias(timestamp->data, diasSubtraidos);
    }
}