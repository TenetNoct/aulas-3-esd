#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "circulo.h"

#define NUM_CIRCULOS 6
#define MAX_COORD 100.0f // Valor máximo para coordenadas x, y
#define MAX_RAIO 20.0f  // Valor máximo para o raio

// Função para gerar um float aleatório entre min e max
float rand_float(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// Função para exibir um vetor de círculos
void exibir_vetor_circulos(Circulo* vetor[], int tamanho) {
    printf("[ ");
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] != NULL) {
            circ_exibe(vetor[i]);
        } else {
            printf("(Círculo NULO)");
        }
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

// Função de ordenação por Seleção (ordena por área crescente)
void ordenar_circulos_por_area_selecao(Circulo* vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int indice_menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            // Compara as áreas usando circ_compara
            if (vetor[j] != NULL && vetor[indice_menor] != NULL && circ_compara(vetor[j], vetor[indice_menor]) < 0) {
                indice_menor = j;
            }
            // Tratar caso um dos círculos seja NULL (colocar no final, por exemplo)
            else if (vetor[j] != NULL && vetor[indice_menor] == NULL) {
                 indice_menor = j; // O não-nulo é menor
            }
        }
        // Troca os ponteiros no vetor
        if (indice_menor != i) {
            Circulo* temp = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = temp;
        }
    }
}


int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // a) Crie um vetor para armazenar 6 círculos
    Circulo* vetor_circulos[NUM_CIRCULOS];
    for(int i=0; i<NUM_CIRCULOS; ++i) vetor_circulos[i] = NULL; // Inicializa com NULL

    printf("--- Questão 2: TAD Círculo ---\n\n");

    // b) Preencha o vetor com 6 círculos com valores aleatórios
    printf("b) Preenchendo o vetor com círculos aleatórios:\n");
    for (int i = 0; i < NUM_CIRCULOS; i++) {
        float x = rand_float(0.0f, MAX_COORD);
        float y = rand_float(0.0f, MAX_COORD);
        float r = rand_float(1.0f, MAX_RAIO); // Raio mínimo de 1.0
        vetor_circulos[i] = circ_cria(x, y, r);
        if (vetor_circulos[i] == NULL) {
            fprintf(stderr, "Erro ao criar círculo %d\n", i);
            // Liberar memória já alocada antes de sair
            for(int j = 0; j < i; j++) {
                circ_libera(&vetor_circulos[j]);
            }
            return 1; // Termina com erro
        }
    }

    // c) Exiba o vetor de círculos.
    printf("\nc) Vetor de círculos original:\n");
    exibir_vetor_circulos(vetor_circulos, NUM_CIRCULOS);

    // d) Ordena o vetor de círculos crescentemente (por área) - Usando Seleção
    printf("\nd) Ordenando o vetor por área (Seleção)...\n");
    ordenar_circulos_por_area_selecao(vetor_circulos, NUM_CIRCULOS);

    // e) Exiba o vetor de círculos após ordenação
    printf("\ne) Vetor de círculos ordenado por área:\n");
    exibir_vetor_circulos(vetor_circulos, NUM_CIRCULOS);

    // Libera a memória alocada para os círculos
    printf("\nLiberando memória...\n");
    for (int i = 0; i < NUM_CIRCULOS; i++) {
        circ_libera(&vetor_circulos[i]);
    }

    printf("\n--- Fim da Questão 2 ---\n");

    return 0;
}