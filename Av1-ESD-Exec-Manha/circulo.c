#include "circulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h> // Para INT_MAX em circ_compara

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Estrutura interna do círculo (não exportada)
struct circulo {
    Ponto* centro;
    float raio;
};

Circulo* circ_cria(float x, float y, float r) {
    if (r < 0) {
        fprintf(stderr, "Erro: Raio não pode ser negativo.\n");
        return NULL;
    }
    Circulo* c = (Circulo*) malloc(sizeof(Circulo));
    if (c == NULL) {
        perror("Erro ao alocar memória para o círculo");
        return NULL;
    }
    c->centro = pto_cria(x, y);
    if (c->centro == NULL) {
        free(c);
        return NULL; // Erro na criação do ponto
    }
    c->raio = r;
    return c;
}

void circ_libera(Circulo** c) {
    if (c != NULL && *c != NULL) {
        pto_libera(&((*c)->centro)); // Libera o ponto associado
        free(*c);
        *c = NULL;
    }
}

float circ_area(Circulo* c) {
    if (c == NULL) {
        fprintf(stderr, "Erro: Círculo NULO para calcular área.\n");
        return -1.0f;
    }
    return M_PI * c->raio * c->raio;
}

int circ_interior(Circulo* c, Ponto* p) {
    if (c == NULL || p == NULL) {
        fprintf(stderr, "Erro: Círculo ou Ponto NULO para verificar interior.\n");
        return 0; // Considera como fora em caso de erro
    }
    float dist = pto_distancia(c->centro, p);
    if (dist < 0) return 0; // Erro na pto_distancia
    return (dist <= c->raio); // Retorna 1 (true) se dist <= raio
}

char* circ_getCirculo(Circulo* c) {
    if (c == NULL) {
        return NULL;
    }
    char* str_centro = pto_getPonto(c->centro);
    if (str_centro == NULL) {
        return NULL;
    }

    // Estima tamanho: "(c:,r:)" + tam(str_centro) + tam(raio) + NUL
    // Ex: "(c:(1.00,2.00),r:5.00)"
    int len_centro = strlen(str_centro);
    char* buffer = (char*) malloc((len_centro + 20) * sizeof(char)); // Tamanho seguro
    if (buffer == NULL) {
        perror("Erro ao alocar memória para string do círculo");
        free(str_centro);
        return NULL;
    }

    sprintf(buffer, "(c:%s,r:%.2f)", str_centro, c->raio);
    free(str_centro); // Libera a string retornada por pto_getPonto
    return buffer;
}

void circ_exibe(Circulo* c) {
    if (c != NULL) {
        char* str_circ = circ_getCirculo(c);
        if (str_circ != NULL) {
            printf("%s", str_circ);
            free(str_circ);
        } else {
            printf("(Erro ao formatar Círculo)");
        }
    } else {
        printf("(Círculo NULO)");
    }
}

int circ_compara(Circulo* c1, Circulo* c2) {
    if (c1 == NULL || c2 == NULL) {
        fprintf(stderr, "Erro: Círculo(s) NULO(s) para comparação.\n");
        return INT_MAX; // Valor grande para indicar erro
    }
    float area1 = circ_area(c1);
    float area2 = circ_area(c2);

    if (area1 < area2) {
        return -1;
    } else if (area1 > area2) {
        return 1;
    } else {
        return 0;
    }
}

Circulo* circ_clona(Circulo* c1) {
    if (c1 == NULL) {
        return NULL;
    }
    float x, y;
    pto_acessa(c1->centro, &x, &y);
    return circ_cria(x, y, c1->raio);
}

float circ_getRaio(Circulo* c) {
    if (c == NULL) {
        return -1.0f;
    }
    return c->raio;
}

Ponto* circ_getCentro(Circulo* c) {
    if (c == NULL) {
        return NULL;
    }
    return c->centro; // Retorna o ponteiro interno, cuidado!
}

void circ_setRaio(Circulo* c, float r) {
    if (c != NULL && r >= 0) {
        c->raio = r;
    }
}

void circ_setCentro(Circulo* c, Ponto* p) {
    if (c != NULL && p != NULL) {
        // Libera o centro antigo antes de atribuir um novo
        pto_libera(&(c->centro));
        // Cria uma cópia do ponto p para evitar compartilhamento
        float x, y;
        pto_acessa(p, &x, &y);
        c->centro = pto_cria(x, y);
        if (c->centro == NULL) {
             // Tenta restaurar um ponto padrão ou lida com o erro
             fprintf(stderr, "Erro crítico: Falha ao recriar o ponto central após setCentro.\n");
             // Poderia tentar criar um ponto (0,0) como fallback?
             // c->centro = pto_cria(0, 0);
        }
    }
}