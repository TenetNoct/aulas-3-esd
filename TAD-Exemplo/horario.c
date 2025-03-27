#include <stdio.h>
#include <stdlib.h>
#include "horario.h"

Horario *criarHorario(int hora, int minuto) {
    // Validação básica dos parâmetros
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        return NULL; // Horário inválido
    }
    
    Horario *novoHorario = (Horario *)malloc(sizeof(Horario));
    if (novoHorario == NULL) {
        return NULL; // Falha na alocação de memória
    }
    
    novoHorario->hora = hora;
    novoHorario->minuto = minuto;
    
    return novoHorario;
}

void imprimirHorario(Horario *horario) {
    if (horario != NULL) {
        printf("%02d:%02d", horario->hora, horario->minuto);
    }
}

void destruirHorario(Horario *horario) {
    free(horario);
}

int somarMinutos(Horario *horario, int minutos) {
    if (horario == NULL || minutos < 0) {
        return 0;
    }
    
    int totalMinutos = horario->hora * 60 + horario->minuto + minutos;
    int diasAdicionados = totalMinutos / (24 * 60);
    
    // Ajusta o horário para o formato de 24 horas
    totalMinutos %= (24 * 60);
    horario->hora = totalMinutos / 60;
    horario->minuto = totalMinutos % 60;
    
    return diasAdicionados;
}

int subtrairMinutos(Horario *horario, int minutos) {
    if (horario == NULL || minutos < 0) {
        return 0;
    }
    
    int totalMinutos = horario->hora * 60 + horario->minuto;
    int diasSubtraidos = 0;
    
    if (minutos > totalMinutos) {
        // Precisamos subtrair dias
        diasSubtraidos = (minutos - totalMinutos) / (24 * 60) + 1;
        minutos %= (24 * 60);
        totalMinutos += diasSubtraidos * 24 * 60;
    }
    
    totalMinutos -= minutos;
    totalMinutos %= (24 * 60);
    
    horario->hora = totalMinutos / 60;
    horario->minuto = totalMinutos % 60;
    
    return diasSubtraidos;
}