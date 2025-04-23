#ifndef PONTO_H
#define PONTO_H

/* Tipo exportado */
typedef struct ponto Ponto;

/* Funu00e7u00f5es exportadas */

/**
 * @brief Aloca e retorna um ponto com coordenadas (x,y).
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @return Ponteiro para o ponto criado ou NULL em caso de erro.
 */
Ponto* pto_cria(float x, float y);

/**
 * @brief Libera a memu00f3ria de um ponto previamente criado.
 * @param p Ponteiro para o ponteiro do ponto.
 */
void pto_libera(Ponto** p);

/**
 * @brief Retorna os valores das coordenadas de um ponto.
 * @param p Ponteiro para o ponto.
 * @param x Ponteiro para armazenar a coordenada x.
 * @param y Ponteiro para armazenar a coordenada y.
 */
void pto_acessa(Ponto* p, float* x, float* y);

/**
 * @brief Atribui novos valores u00e0s coordenadas de um ponto.
 * @param p Ponteiro para o ponto.
 * @param x Nova coordenada x.
 * @param y Nova coordenada y.
 */
void pto_atribui(Ponto* p, float x, float y);

/**
 * @brief Retorna a distu00e2ncia entre dois pontos.
 * @param p1 Ponteiro para o primeiro ponto.
 * @param p2 Ponteiro para o segundo ponto.
 * @return A distu00e2ncia euclidiana entre p1 e p2.
 */
float pto_distancia(Ponto* p1, Ponto* p2);

/**
 * @brief Retorna uma string com os valores do ponto no formato "(x.xx,y.yy)".
 *        A string retornada deve ser liberada pelo chamador usando free().
 * @param p Ponteiro para o ponto.
 * @return String formatada ou NULL em caso de erro.
 */
char* pto_getPonto(Ponto* p);

/**
 * @brief Escreve na tela o ponto no formato "(xxx.xx,yyy.yy)".
 * @param p Ponteiro para o ponto.
 */
void pto_exibe(Ponto* p);

/**
 * @brief Compara dois pontos em relau00e7u00e3o u00e0 distu00e2ncia da origem (0,0).
 * @param pt1 Ponteiro para o primeiro ponto.
 * @param pt2 Ponteiro para o segundo ponto.
 * @return 1 se pt1 estu00e1 mais pru00f3ximo da origem que pt2, 0 caso contru00e1rio (incluindo empate).
 */
int pto_menorque(Ponto* pt1, Ponto* pt2);

#endif // PONTO_H