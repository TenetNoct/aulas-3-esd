#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "data.h"
#include "horario.h"

/**
 * Estrutura que une Data e Horário, permitindo manipular tempo de forma completa.
 */
typedef struct {
    Data *data;
    Horario *horario;
} Timestamp;

/**
 * Cria um timestamp com Data e Horário.
 * 
 * @param dia O dia da data.
 * @param mes O mês da data.
 * @param ano O ano da data.
 * @param hora A hora do horário.
 * @param minuto O minuto do horário.
 * @return Ponteiro para a estrutura Timestamp alocada.
 */
Timestamp *criarTimestamp(int dia, int mes, int ano, int hora, int minuto);

/**
 * Exibe data e horário no formato DD/MM/AAAA HH:MM.
 * 
 * @param timestamp Ponteiro para a estrutura Timestamp.
 */
void imprimirTimestamp(Timestamp *timestamp);

/**
 * Libera memória da estrutura Timestamp.
 * 
 * @param timestamp Ponteiro para a estrutura Timestamp.
 */
void destruirTimestamp(Timestamp *timestamp);

/**
 * Adiciona minutos ao timestamp, ajustando data e horário.
 * 
 * @param timestamp Ponteiro para a estrutura Timestamp.
 * @param minutos Número de minutos a adicionar.
 */
void somarMinutosTimestamp(Timestamp *timestamp, int minutos);

/**
 * Subtrai minutos, garantindo consistência entre data e horário.
 * 
 * @param timestamp Ponteiro para a estrutura Timestamp.
 * @param minutos Número de minutos a subtrair.
 */
void subtrairMinutosTimestamp(Timestamp *timestamp, int minutos);

#endif /* TIMESTAMP_H */