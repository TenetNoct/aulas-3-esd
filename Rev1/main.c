#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 3




void horario(int tempo, int *horas, int *minutos);

struct tat{
	int tempo,cod;
    char nome[30];
};

typedef struct tat tAtleta;

void obtemAtleta(int num,  tAtleta *atleta){

    printf("\nDigite o código do %dº atleta:",num);
	scanf("%i",&atleta->cod);  // (*atleta).cod   pode ser escrito como atleta->cod
	
    printf("\n Digite o nome do atleta:");
	scanf("%s",&atleta->nome);

	printf("\nDigite o tempo do %dº atleta:",num);
	scanf("%i",&atleta->tempo);
	return;
}

/*
    tAtleta leAtleta(int num){
        tAtleta atleta;
        printf("\nDigite o código do %dº atleta:",num);
        scanf("%i",&atleta.cod);
        
        printf("\nDigite o tempo do %dº atleta:",num);
        scanf("%i",&atleta.tempo);
        return atleta;
    }
*/

void trocaAtletas(tAtleta *a, tAtleta *b) {
    tAtleta temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortAtletas(tAtleta *atletas, int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (atletas[j].tempo > atletas[j+1].tempo) {
                trocaAtletas(&atletas[j], &atletas[j+1]);
            }
            else if (atletas[j].tempo == atletas[j+1].tempo) {
                if (strcmp(atletas[j].nome, atletas[j+1].nome) > 0) {
                    trocaAtletas(&atletas[j], &atletas[j+1]);
                }
            }
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
	tAtleta vAtletas[TAM];

	int tempo_horas, tempo_minutos;
	int maiorTempo = -1, qtMaior= 0, contador, op;
	
    
    for(contador=0;contador<TAM;contador++){
        //atleta=leAtleta(contador+1);
        obtemAtleta(contador+1, &vAtletas[contador]);

	    horario(vAtletas[contador].tempo,&tempo_horas, &tempo_minutos);
	    printf("\nTempo do %dº atleta foi %02i:%02ih", contador + 1, tempo_horas,tempo_minutos);
	}
    
    bubbleSortAtletas(vAtletas, TAM);
    
    printf("\n\nAtletas ordenados por tempo (menor para maior) e nome (ordem alfabética):");
    for(contador=0;contador<TAM;contador++){
        horario(vAtletas[contador].tempo, &tempo_horas, &tempo_minutos);
        printf("\nAtleta: %s, Código: %d, Tempo: %02i:%02ih", 
               vAtletas[contador].nome, 
               vAtletas[contador].cod,
               tempo_horas, 
               tempo_minutos);
    }

	return 0;
}

int divisaoInteira(int dividendo, int divisor, int* quoc, int*resto){
    
    if (divisor==0)
        if (dividendo==0)
            return -1;
        else
            return 0;
    else{
        *quoc= dividendo/divisor;
        *resto=dividendo%divisor;
        return 1;
    }
    
}
void horario(int tempo, int *horas, int *minutos) {
	divisaoInteira(tempo,60, horas,minutos);
	return;
}
