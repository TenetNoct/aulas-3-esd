#ifndef CIRCULO_H
#define CIRCULO_H

#include "ponto.h"
#include <stdbool.h> // Para usar bool no circ_interior

/* Tipo exportado */
typedef struct circulo Circulo;

/* Funções exportadas */

/**
 * @brief Aloca e retorna um círculo com centro (x,y) e raio r.
 * @param x Coordenada x do centro.
 * @param y Coordenada y do centro.
 * @param r Raio do círculo.
 * @return Ponteiro para o círculo criado ou NULL em caso de erro.
 */
Circulo* circ_cria(float x, float y, float r);

/**
 * @brief Libera a memória de um círculo previamente criado.
 *        Também libera a memória do ponto central associado.
 * @param c Ponteiro para o ponteiro do círculo.
 */
void circ_libera(Circulo** c);

/**
 * @brief Retorna o valor da área do círculo.
 * @param c Ponteiro para o círculo.
 * @return A área do círculo (pi * r^2) ou -1.0f em caso de erro.
 */
float circ_area(Circulo* c);

/**
 * @brief Verifica se um dado ponto p está dentro do círculo.
 * @param c Ponteiro para o círculo.
 * @param p Ponteiro para o ponto.
 * @return 1 (true) se o ponto está dentro ou na borda, 0 (false) caso contrário ou erro.
 */
int circ_interior(Circulo* c, Ponto* p);

/**
 * @brief Retorna uma string representando o círculo no formato "(c:centro,r:raio)".
 *        Exemplo: "(c:(1.00,2.00),r:5.00)"
 *        A string retornada deve ser liberada pelo chamador usando free().
 * @param c Ponteiro para o círculo.
 * @return String formatada ou NULL em caso de erro.
 */
char* circ_getCirculo(Circulo* c);

/**
 * @brief Escreve na tela o círculo no formato "(c:centro,r:raio)".
 * @param c Ponteiro para o círculo.
 */
void circ_exibe(Circulo* c);

/**
 * @brief Compara dois círculos com base em suas áreas.
 * @param c1 Ponteiro para o primeiro círculo.
 * @param c2 Ponteiro para o segundo círculo.
 * @return < 0 se area(c1) < area(c2), 0 se area(c1) == area(c2), > 0 se area(c1) > area(c2).
 *         Retorna um valor grande (como INT_MAX) se houver erro.
 */
int circ_compara(Circulo* c1, Circulo* c2);

/**
 * @brief Cria um novo círculo que é uma cópia exata do círculo recebido.
 * @param c1 Ponteiro para o círculo a ser clonado.
 * @return Ponteiro para o novo círculo clonado ou NULL em caso de erro.
 */
Circulo* circ_clona(Circulo* c1);

/**
 * @brief Obtém o raio do círculo.
 * @param c Ponteiro para o círculo.
 * @return O valor do raio ou -1.0f em caso de erro.
 */
float circ_getRaio(Circulo* c);

/**
 * @brief Obtém o ponto central do círculo.
 * @param c Ponteiro para o círculo.
 * @return Ponteiro para o ponto central (não fazer free neste ponteiro!). Retorna NULL se erro.
 */
Ponto* circ_getCentro(Circulo* c);

/**
 * @brief Define um novo raio para o círculo.
 * @param c Ponteiro para o círculo.
 * @param r Novo valor do raio (deve ser não negativo).
 */
void circ_setRaio(Circulo* c, float r);

/**
 * @brief Define um novo ponto central para o círculo.
 *        A função fará uma cópia do ponto p, não armazenará o ponteiro p diretamente.
 * @param c Ponteiro para o círculo.
 * @param p Ponteiro para o novo ponto central.
 */
void circ_setCentro(Circulo* c, Ponto* p);


#endif // CIRCULO_H