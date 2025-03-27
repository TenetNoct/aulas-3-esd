#ifndef DATA_H
#define DATA_H

/**
 * Estrutura que representa uma data com dia, mês e ano.
 */
typedef struct {
    int dia, mes, ano;
} Data;

/**
 * Cria e inicializa uma estrutura Data.
 * 
 * @param dia O dia da data.
 * @param mes O mês da data.
 * @param ano O ano da data.
 * @return Ponteiro para a estrutura Data alocada.
 */
Data *criarData(int dia, int mes, int ano);

/**
 * Exibe a data no formato DD/MM/AAAA.
 * 
 * @param data Ponteiro para a estrutura Data.
 */
void imprimirData(Data *data);

/**
 * Libera a memória alocada para uma estrutura Data.
 * 
 * @param data Ponteiro para a estrutura Data.
 */
void destruirData(Data *data);

/**
 * Adiciona um número de dias à data, ajustando corretamente os meses e anos.
 * 
 * @param data Ponteiro para a estrutura Data.
 * @param dias Número de dias a adicionar.
 */
void somarDias(Data *data, int dias);

/**
 * Subtrai um número de dias da data, garantindo ajustes corretos.
 * 
 * @param data Ponteiro para a estrutura Data.
 * @param dias Número de dias a subtrair.
 */
void subtrairDias(Data *data, int dias);

#endif /* DATA_H */