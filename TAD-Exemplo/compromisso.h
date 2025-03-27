#ifndef COMPROMISSO_H
#define COMPROMISSO_H

#include "timestamp.h"

/**
 * Estrutura que representa um compromisso com data, horário e descrição.
 */
typedef struct {
    Timestamp *timestamp;
    char descricao[100];
} Compromisso;

/**
 * Cria um compromisso.
 * 
 * @param dia O dia da data.
 * @param mes O mês da data.
 * @param ano O ano da data.
 * @param hora A hora do horário.
 * @param minuto O minuto do horário.
 * @param descricao A descrição do compromisso.
 * @return Ponteiro para a estrutura Compromisso alocada.
 */
Compromisso *criarCompromisso(int dia, int mes, int ano, int hora, int minuto, char *descricao);

/**
 * Exibe os detalhes do compromisso.
 * 
 * @param dado Ponteiro para a estrutura Compromisso (como void*).
 */
void imprimirCompromisso(void *dado);

/**
 * Libera memória da estrutura Compromisso.
 * 
 * @param compromisso Ponteiro para a estrutura Compromisso.
 */
void destruirCompromisso(Compromisso *compromisso);

/**
 * Adia um compromisso em minutos.
 * 
 * @param compromisso Ponteiro para a estrutura Compromisso.
 * @param minutos Número de minutos a adiar.
 */
void adiarCompromisso(Compromisso *compromisso, int minutos);

/**
 * Antecipar um compromisso.
 * 
 * @param compromisso Ponteiro para a estrutura Compromisso.
 * @param minutos Número de minutos a antecipar.
 */
void anteciparCompromisso(Compromisso *compromisso, int minutos);

#endif /* COMPROMISSO_H */