#include "ponto.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Estrutura interna do ponto (não exportada)
struct ponto {
    float x;
    float y;
};

Ponto* pto_cria(float x, float y) {
    Ponto* p = (Ponto*) malloc(sizeof(Ponto));
    if (p == NULL) {
        perror("Erro ao alocar memória para o ponto");
        return NULL;
    }
    p->x = x;
    p->y = y;
    return p;
}

void pto_libera(Ponto** p) {
    if (p != NULL && *p != NULL) {
        free(*p);
        *p = NULL; // Evita dangling pointers
    }
}

void pto_acessa(Ponto* p, float* x, float* y) {
    if (p != NULL) {
        if (x != NULL) *x = p->x;
        if (y != NULL) *y = p->y;
    }
}

void pto_atribui(Ponto* p, float x, float y) {
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
}

float pto_distancia(Ponto* p1, Ponto* p2) {
    if (p1 == NULL || p2 == NULL) {
        fprintf(stderr, "Erro: Ponto(s) inválido(s) para calcular distância.\n");
        return -1.0f; // Valor inválido para indicar erro
    }
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    return sqrt(dx*dx + dy*dy);
}

char* pto_getPonto(Ponto* p) {
    if (p == NULL) {
        return NULL;
    }
    // Estima um tamanho seguro para o buffer
    // Formato: "(xxx.xx,yyy.yy)" + NUL
    char* buffer = (char*) malloc(50 * sizeof(char)); // Tamanho generoso
    if (buffer == NULL) {
        perror("Erro ao alocar memória para string do ponto");
        return NULL;
    }
    sprintf(buffer, "(%.2f,%.2f)", p->x, p->y);
    return buffer;
}

void pto_exibe(Ponto* p) {
    if (p != NULL) {
        printf("(%.2f,%.2f)", p->x, p->y);
    } else {
        printf("(Ponto NULO)");
    }
}

int pto_menorque(Ponto* pt1, Ponto* pt2) {
    if (pt1 == NULL || pt2 == NULL) {
        fprintf(stderr, "Erro: Ponto(s) inválido(s) para comparação.\n");
        return -1; // Indica erro
    }
    // Calcula a distância ao quadrado da origem para evitar sqrt
    float dist1_sq = pt1->x * pt1->x + pt1->y * pt1->y;
    float dist2_sq = pt2->x * pt2->x + pt2->y * pt2->y;

    return (dist1_sq < dist2_sq); // Retorna 1 se pt1 mais próximo, 0 cc
}