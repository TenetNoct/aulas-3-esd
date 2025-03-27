#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

int main() {
    // Criar uma agenda
    Agenda *minhaAgenda = criarAgenda(5);
    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda!\n");
        return 1;
    }
    
    // Adicionar alguns compromissos
    Compromisso *comp1 = criarCompromisso(10, 5, 2023, 14, 30, "Reuniao de trabalho");
    Compromisso *comp2 = criarCompromisso(15, 5, 2023, 9, 0, "Consulta medica");
    Compromisso *comp3 = criarCompromisso(15, 5, 2023, 16, 45, "Aula de ingles");
    Compromisso *comp4 = criarCompromisso(20, 5, 2023, 19, 0, "Jantar com amigos");
    
    adicionarCompromisso(minhaAgenda, comp1);
    adicionarCompromisso(minhaAgenda, comp2);
    adicionarCompromisso(minhaAgenda, comp3);
    adicionarCompromisso(minhaAgenda, comp4);
    
    // Listar todos os compromissos
    printf("\n=== Todos os Compromissos ===\n");
    listarCompromissos(minhaAgenda);
    
    // Consultar compromissos por data
    printf("\n=== Consulta por Data ===\n");
    consultarCompromissosPorData(minhaAgenda, 15, 5, 2023);
    
    // Adiar um compromisso
    printf("\n=== Adiando Compromisso ===\n");
    printf("Antes: ");
    imprimirCompromisso(minhaAgenda->compromissos[0]);
    
    alterarHorarioCompromisso(minhaAgenda, 0, 60, 1); // Adiar 60 minutos
    
    printf("Depois: ");
    imprimirCompromisso(minhaAgenda->compromissos[0]);
    
    // Antecipar um compromisso
    printf("\n=== Antecipando Compromisso ===\n");
    printf("Antes: ");
    imprimirCompromisso(minhaAgenda->compromissos[1]);
    
    alterarHorarioCompromisso(minhaAgenda, 1, 30, 0); // Antecipar 30 minutos
    
    printf("Depois: ");
    imprimirCompromisso(minhaAgenda->compromissos[1]);
    
    // Remover um compromisso
    printf("\n=== Removendo Compromisso ===\n");
    removerCompromisso(minhaAgenda, 2);
    
    // Listar compromissos após remoção
    printf("\n=== Compromissos Após Remoção ===\n");
    listarCompromissos(minhaAgenda);
    
    // Demonstração de operações com Data
    printf("\n=== Operações com Data ===\n");
    Data *data = criarData(28, 2, 2024); // 2024 é bissexto
    printf("Data original: ");
    imprimirData(data);
    
    somarDias(data, 2);
    printf("\nApós somar 2 dias: ");
    imprimirData(data);
    
    subtrairDias(data, 5);
    printf("\nApós subtrair 5 dias: ");
    imprimirData(data);
    
    destruirData(data);
    
    // Demonstração de operações com Horário
    printf("\n\n=== Operações com Horário ===\n");
    Horario *horario = criarHorario(23, 45);
    printf("Horário original: ");
    imprimirHorario(horario);
    
    int dias = somarMinutos(horario, 30);
    printf("\nApós somar 30 minutos: ");
    imprimirHorario(horario);
    printf(" (Dias adicionados: %d)", dias);
    
    dias = subtrairMinutos(horario, 60);
    printf("\nApós subtrair 60 minutos: ");
    imprimirHorario(horario);
    printf(" (Dias subtraídos: %d)", dias);
    
    destruirHorario(horario);
    
    // Liberar memória
    destruirAgenda(minhaAgenda);
    
    printf("\n\nPrograma finalizado com sucesso!\n");
    return 0;
}