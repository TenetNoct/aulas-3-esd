#ifndef HORARIO_H
#define HORARIO_H

/**
 * Estrutura que representa um horário com hora e minuto.
 */
typedef struct {
    int hora, minuto;
} Horario;

/**
 * Cria e inicializa um Horario.
 * 
 * @param hora A hora do horário (0-23).
 * @param minuto O minuto do horário (0-59).
 * @return Ponteiro para a estrutura Horario alocada.
 */
Horario *criarHorario(int hora, int minuto);

/**
 * Exibe o horário no formato HH:MM.
 * 
 * @param horario Ponteiro para a estrutura Horario.
 */
void imprimirHorario(Horario *horario);

/**
 * Libera a memória alocada para Horario.
 * 
 * @param horario Ponteiro para a estrutura Horario.
 */
void destruirHorario(Horario *horario);

/**
 * Adiciona minutos ao horário, ajustando corretamente as horas.
 * 
 * @param horario Ponteiro para a estrutura Horario.
 * @param minutos Número de minutos a adicionar.
 * @return Número de dias adicionados (se ultrapassar 24 horas).
 */
int somarMinutos(Horario *horario, int minutos);

/**
 * Subtrai minutos, retrocedendo corretamente as horas.
 * 
 * @param horario Ponteiro para a estrutura Horario.
 * @param minutos Número de minutos a subtrair.
 * @return Número de dias subtraídos (se necessário).
 */
int subtrairMinutos(Horario *horario, int minutos);

#endif /* HORARIO_H */