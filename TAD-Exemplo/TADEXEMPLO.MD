Em muitos sistemas, como agendas pessoais, softwares de produtividade, sistemas de gerenciamento
de tarefas e calendários eletrônicos, há a necessidade de:
1. Registrar compromissos com data e horário específicos.
2. Consultar compromissos marcados para uma determinada data.
3. Remover compromissos da agenda caso sejam cancelados.
4. Ajustar horários de compromissos, seja para adiá-los ou antecipá-los.
Esse problema envolve manipulação de datas e horários, exigindo operações matemáticas que levem
em consideração:  Variações no número de dias dos meses.  Anos bissextos. x
 Mudanças de dias ao ultrapassar a meia-noite (00:00).
Para resolver esse problema, foi necessário criar estruturas modulares que possibilitem essas operações
de maneira eficiente e sem inconsistências.
Para resolver o problema da gestão de compromissos, foram desenvolvidos os seguintes Tipos
Abstratos de Dados (TADs):
1. TAD Data
 Representa uma data com dia, mês e ano.  Permite a soma e subtração de dias, garantindo ajustes de meses e anos corretamente.  Considera anos bissextos na contagem de dias. x
2. TAD Horário
 Representa um horário com horas e minutos.  Permite a soma e subtração de minutos, ajustando automaticamente a hora ao ultrapassar
24h.
3. TAD Timestamp
 Une a data e o horário em uma única estrutura.  Permite operações combinadas de tempo, como adicionar minutos e ajustar automaticamente
a data.  Facilita a manipulação de informações temporais em compromissos.
4. TAD Compromisso
 Armazena um timestamp (data e horário) e uma descrição.  Permite:
o Criação e destruição de compromissos.
o Impressão de detalhes do compromisso.
o Adiantamento e adiamento de compromissos em minutos, ajustando
automaticamente a data e o horário.
5. TAD Agenda
 Gerencia uma coleção de compromissos.  Permite:
o Adicionar compromissos à agenda.
o Listar compromissos armazenados.
o Remover compromissos por índice.
o Consultar compromissos em uma data específica.
o Alterar o horário de um compromisso, permitindo antecipação e adiamento. Funcionalidades:
1. Registrar compromissos com data e horário.
2. Consultar compromissos de uma data específica.
3. Listar todos os compromissos armazenados na agenda.
4. Remover um compromisso da agenda.
5. Alterar um compromisso existente, permitindo:
o Adiá-lo (aumentando minutos no horário).
o Antecipá-lo (reduzindo minutos no horário).
Descrição Detalhada da Estrutura e Funcionalidades dos TADs
A solução desenvolvida para gerenciar compromissos em uma agenda utiliza um conjunto de Tipos
Abstratos de Dados (TADs), cada um com uma função específica para garantir modularidade,
reutilização e eficiência na manipulação de datas, horários e eventos.
1. TAD Data
1.1 Estrutura
O TAD Data é responsável por armazenar e manipular informações de dia, mês e ano. Ele garante que
operações com datas sejam feitas corretamente, considerando o número de dias de cada mês e os anos
bissextos.
Definição da Estrutura
c
typedef struct {
 int dia, mes, ano;
} Data;
1.2 Funcionalidades
Função Descrição
Data *criarData(int dia, int mes, int ano) Aloca e inicializa uma estrutura Data.
void imprimirData(Data *data) Exibe a data no formato DD/MM/AAAA. void destruirData(Data *data) Libera a memória alocada para uma estrutura Data.
void somarDias(Data *data, int dias) Adiciona um número de dias à data, ajustando corretamente os
meses e anos.
void subtrairDias(Data *data, int dias) Subtrai um número de dias da data, garantindo ajustes corretos.
1.3 Lógica de Operação
1. Criação da Data
o O usuário define dia, mês e ano ao criar a estrutura.
2. Impressão da Data
o A função imprimirData() exibe a data corretamente no formato DD/MM/AAAA. 3. Soma e Subtração de Dias
o A função verifica quantos dias o mês possui e ajusta corretamente a data ao
ultrapassar os limites.
o Para subtração, se a data for anterior ao início do mês, retrocede para o mês anterior,
considerando os dias desse mês.
2. TAD Horário
2.1 Estrutura
O TAD Horário gerencia horas e minutos, permitindo operações de soma e subtração de tempo.
Definição da Estrutura
typedef struct {
 int hora, minuto;
} Horario;
2.2 Funcionalidades
Função Descrição
Horario *criarHorario(int hora, int minuto) Cria e inicializa um Horario.
void imprimirHorario(Horario *horario) Exibe o horário no formato HH:MM.
void destruirHorario(Horario *horario) Libera a memória alocada para Horario.
void somarMinutos(Horario *horario, int minutos) Adiciona minutos ao horário, ajustando corretamente
as horas.
void subtrairMinutos(Horario *horario, int minutos) Subtrai minutos, retrocedendo corretamente as horas.
2.3 Lógica de Operação
1. Criação do Horário
o O usuário fornece hora e minuto ao criar a estrutura.
2. Impressão do Horário
o imprimirHorario() exibe corretamente no formato HH:MM.
3. Soma e Subtração de Minutos
o Se ultrapassar 60 minutos, os minutos são convertidos em horas. o Se ultrapassar 24 horas, o horário reseta e pode indicar necessidade de ajuste na data.
o A subtração lida com minutos negativos, ajustando corretamente as horas.
3. TAD Timestamp (Data + Horário)
3.1 Estrutura
O TAD Timestamp une Data e Horário, permitindo manipular tempo de forma completa.
Definição da Estrutura
typedef struct {
 Data *data;
 Horario *horario;
} Timestamp;
3.2 Funcionalidades
Função Descrição
Timestamp *criarTimestamp(int dia, int mes, int ano, int hora, int minuto) Cria um timestamp com Data e Horário.void imprimirTimestamp(Timestamp *timestamp) Exibe data e horário no formato
DD/MM/AAAA HH:MM.
void destruirTimestamp(Timestamp *timestamp) Libera memória da estrutura Timestamp.void somarMinutosTimestamp(Timestamp *timestamp, int minutos) Adiciona minutos ao timestamp,
ajustando data e horário.
void subtrairMinutosTimestamp(Timestamp *timestamp, int minutos) Subtrai minutos, garantindo consistência entre data e horário.
3.3 Lógica de Operação
 Operações de soma e subtração de minutos podem alterar a data ao ultrapassar limites de
horas.  O timestamp é essencial para a gestão de compromissos.
4. TAD Compromisso
4.1 Estrutura
Cada compromisso possui um Timestamp e uma descrição. Definição da Estrutura
typedef struct {
 Timestamp *timestamp;
 char descricao[100];
} Compromisso;
4.2 Funcionalidades
Função Descrição
Compromisso *criarCompromisso(int dia, int mes, int ano, int hora, int minuto,
char *descricao) Cria um compromisso.
void imprimirCompromisso(void *dado) Exibe os detalhes do
compromisso.
void destruirCompromisso(Compromisso *compromisso) Libera memória.
void adiarCompromisso(Compromisso *compromisso, int minutos) Adia um compromisso em
minutos.
void anteciparCompromisso(Compromisso *compromisso, int minutos) Antecipar um
compromisso.
5. TAD Agenda
5.1 Estrutura
A agenda gerencia uma coleção de compromissos armazenados em um vetor dinâmico.
Definição da Estrutura
typedef struct {
 Compromisso **compromissos;
 int tamanho;
 int capacidade;
} Agenda;
5.2 Funcionalidades
Função Descrição
Agenda *criarAgenda(int capacidadeInicial) Cria uma agenda dinâmica.
void adicionarCompromisso(Agenda *agenda, Compromisso
*compromisso)
Adiciona um compromisso à
agenda.
void listarCompromissos(Agenda *agenda) Exibe todos os compromissos
armazenados.
void removerCompromisso(Agenda *agenda, int indice) Remove um compromisso da
agenda.
void consultarCompromissosPorData(Agenda *agenda, int dia, int
mes, int ano)
Busca compromissos em uma
data específica.
void alterarHorarioCompromisso(Agenda *agenda, int indice, int
minutos, int adiar)