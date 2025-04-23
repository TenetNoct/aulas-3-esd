Questão 2) Usando os TADs Data e Produto, construa uma main que:

a) crie um vetor para armazenar 6 produtos
b) preencha o vetor com 6 produtos. ( sem leitura de dados)
c) Mostre para cada produto: seu nome e mês por extenso que o produto estará fora da
validade

I

// Representação do TAD: TData
//-----------
// Interface
//-----------
typedef struct data tData;
/* Funções exportadas */
/* Função cria - Aloca e retorna uma data
dia/mes/ano */
tData* dta_cria(int dia, int mes, int ano);
/* Função libera - Libera memória de uma Data
criada */
void dta_libera(tData* p);
/* Função acessa - Retorna os valores de uma Data
*/
void dta_acessa(tData* p, int* dia, int* mes, int*
ano);
/* Função atribui - Atribui novos valores à Data
*/
void dta_atribui(tData* p, int dia, int mes, int
ano);
/* Função Intervalo - Retorna a data após X dias
*/
tData* dta_intervalo(tData* p1, int X);
/* Função Exibe - Escreve na tela a data no
formato dd/mm/aaaa */
tData* dta_exibe(tData* p1);
/* Função getData - Retorna uma string com os
valores da data no formato dd/mm/aaaa*/
char* dta_getData(tData* p);

/* Função maiorIgual - Recebe duas datas e retorna
1 se a dta1 for maior ou igual a data 2 (mais
recente) ou 0 caso contrário
12/10/2022 é maior ou igual a 12/09/2022
*/
int dta_maiorIgual(tData* p1, tData* p2);
/* Função dta_MesExtensol - Recebe uma data e
retorna o mês da data por extenso*/
char* dta_MesExtenso(tData*p);
____________________________________________
// Representação do TAD: tProduto
typedef struct tProd tProduto;
/*
Um produto possui:
nome: string
codBarras: string;
dta de Fabricação: Data
dias de validade:int
preco: float
*/
//Interface
//cria um produto: recebe nome, codBarras,
dia,mes,ano da fabricação, n de dias da validade,
preço

tProduto * prod_cria(char*id, char*codBarras,int
dia, int mes, int ano, int val, float pr);
// exibe o produto
void prod_Exibir(tProduto *p);
// verifica se o produto está na validade na data
fornecida
int prod_estaNaValidade(tProduto *p,tData*dta);
int prod_ehSemelhante(tProduto *p1, tProduto* p2);
void prod_reajusta(tProduto *p, float perc) ;
//get para cada atributo
// retorna o nome do produto
char * prod_get_Id(tProduto * p);