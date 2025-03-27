#ifndef AGENDA_H
#define AGENDA_H

#include "compromisso.h"

/**
 * Estrutura que gerencia uma coleção de compromissos.
 */
typedef struct {
    Compromisso **compromissos;
    int tamanho;
    int capacidade;
} Agenda;

/**
 * Cria uma agenda dinâmica.
 * 
 * @param capacidadeInicial Capacidade inicial da agenda.
 * @return Ponteiro para a estrutura Agenda alocada.
 */
Agenda *criarAgenda(int capacidadeInicial);

/**
 * Adiciona um compromisso à agenda.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 * @param compromisso Ponteiro para o compromisso a ser adicionado.
 */
void adicionarCompromisso(Agenda *agenda, Compromisso *compromisso);

/**
 * Exibe todos os compromissos armazenados.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 */
void listarCompromissos(Agenda *agenda);

/**
 * Remove um compromisso da agenda.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 * @param indice Índice do compromisso a ser removido.
 */
void removerCompromisso(Agenda *agenda, int indice);

/**
 * Busca compromissos em uma data específica.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 * @param dia O dia da data.
 * @param mes O mês da data.
 * @param ano O ano da data.
 */
void consultarCompromissosPorData(Agenda *agenda, int dia, int mes, int ano);

/**
 * Altera o horário de um compromisso.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 * @param indice Índice do compromisso a ser alterado.
 * @param minutos Número de minutos a adiar ou antecipar.
 * @param adiar Flag que indica se é para adiar (1) ou antecipar (0).
 */
void alterarHorarioCompromisso(Agenda *agenda, int indice, int minutos, int adiar);

/**
 * Libera memória da estrutura Agenda.
 * 
 * @param agenda Ponteiro para a estrutura Agenda.
 */
void destruirAgenda(Agenda *agenda);

#endif /* AGENDA_H */