#include <stdio.h>
#include <stdlib.h>
#include "data.h"

// Função auxiliar para verificar se um ano é bissexto
static int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Função auxiliar para obter o número de dias em um mês
static int diasNoMes(int mes, int ano) {
    int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (mes == 2 && ehBissexto(ano)) {
        return 29;
    }
    
    return dias[mes];
}

// Função auxiliar para validar uma data
static int dataValida(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12) {
        return 0;
    }
    
    int maxDias = diasNoMes(mes, ano);
    if (dia < 1 || dia > maxDias) {
        return 0;
    }
    
    return 1;
}

Data *criarData(int dia, int mes, int ano) {
    if (!dataValida(dia, mes, ano)) {
        return NULL; // Data inválida
    }
    
    Data *novaData = (Data *)malloc(sizeof(Data));
    if (novaData == NULL) {
        return NULL; // Falha na alocação de memória
    }
    
    novaData->dia = dia;
    novaData->mes = mes;
    novaData->ano = ano;
    
    return novaData;
}

void imprimirData(Data *data) {
    if (data != NULL) {
        printf("%02d/%02d/%04d", data->dia, data->mes, data->ano);
    }
}

void destruirData(Data *data) {
    free(data);
}

void somarDias(Data *data, int dias) {
    if (data == NULL || dias < 0) {
        return;
    }
    
    while (dias > 0) {
        int diasRestantesNoMes = diasNoMes(data->mes, data->ano) - data->dia + 1;
        
        if (dias < diasRestantesNoMes) {
            data->dia += dias;
            break;
        } else {
            dias -= diasRestantesNoMes;
            data->mes++;
            data->dia = 1;
            
            if (data->mes > 12) {
                data->mes = 1;
                data->ano++;
            }
        }
    }
}

void subtrairDias(Data *data, int dias) {
    if (data == NULL || dias < 0) {
        return;
    }
    
    while (dias > 0) {
        if (dias < data->dia) {
            data->dia -= dias;
            break;
        } else {
            dias -= data->dia;
            data->mes--;
            
            if (data->mes < 1) {
                data->mes = 12;
                data->ano--;
            }
            
            data->dia = diasNoMes(data->mes, data->ano);
        }
    }
}