#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "data.h"
#include "produto.h"


int main(){

    tProd vet[6];
    tData* dtaTemp;
    int i, temp;

    for(i=0;i<6;i++){
        vet[i] = prod_cria("produto", "codBarras", 1, 1, 2023, 1, 1.0);
    }

    for(i=0;i<6;i++){
        printf("%s\n", prod_get_Id(vet[i])); //imprimindo o nome do produto
        dtaTemp = dta_intervalo(vet[i].dtaFabricacao, vet[i].diasValidade); //atribuindo a data de validade do produto a variavel dtaTemp

        printf("%s\n", dta_MesExtenso(dtaTemp)); //imprimindo a data de validade do produto
        free(dtaTemp); //liberando a memória alocada para a data de validad
    }

    return 0;
}
