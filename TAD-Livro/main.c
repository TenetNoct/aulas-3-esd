#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "estante.h"

#define MAX_ESTANTES 5

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenuPrincipal() {
    printf("\n===== SISTEMA DE GERENCIAMENTO DE LIVROS E ESTANTES =====\n");
    printf("1. Gerenciar Estantes\n");
    printf("2. Gerenciar Livros\n");
    printf("3. Buscar Livro\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

void exibirMenuEstantes() {
    printf("\n===== GERENCIAMENTO DE ESTANTES =====\n");
    printf("1. Criar Nova Estante\n");
    printf("2. Listar Estantes\n");
    printf("3. Renomear Estante\n");
    printf("4. Excluir Estante\n");
    printf("5. Voltar\n");
    printf("Escolha uma opcao: ");
}

void exibirMenuLivros() {
    printf("\n===== GERENCIAMENTO DE LIVROS =====\n");
    printf("1. Adicionar Livro\n");
    printf("2. Listar Livros de uma Estante\n");
    printf("3. Editar Livro\n");
    printf("4. Remover Livro\n");
    printf("5. Ordenar Livros por Nome\n");
    printf("6. Voltar\n");
    printf("Escolha uma opcao: ");
}

int main() {
    TEstante *estantes[MAX_ESTANTES];
    int numEstantes = 0;
    int opcaoPrincipal, opcaoEstantes, opcaoLivros;
    int indiceEstante, indiceLivro;
    char nome[100], autor[100], novoNome[100];
    int paginas, ano;
    
    // Inicializar array de estantes
    for (int i = 0; i < MAX_ESTANTES; i++) {
        estantes[i] = NULL;
    }
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcaoPrincipal);
        limparBuffer();
        
        switch (opcaoPrincipal) {
            case 1: // Gerenciar Estantes
                do {
                    exibirMenuEstantes();
                    scanf("%d", &opcaoEstantes);
                    limparBuffer();
                    
                    switch (opcaoEstantes) {
                        case 1: // Criar Nova Estante
                            if (numEstantes < MAX_ESTANTES) {
                                printf("Digite o nome da estante: ");
                                fgets(nome, sizeof(nome), stdin);
                                nome[strcspn(nome, "\n")] = '\0'; // Remover o \n do final
                                
                                estantes[numEstantes] = criarEstante();
                                if (estantes[numEstantes] != NULL) {
                                    editarEstante(estantes[numEstantes], nome);
                                    printf("Estante '%s' criada com sucesso!\n", nome);
                                    numEstantes++;
                                } else {
                                    printf("Erro ao criar estante!\n");
                                }
                            } else {
                                printf("Numero maximo de estantes atingido!\n");
                            }
                            break;
                            
                        case 2: // Listar Estantes
                            if (numEstantes > 0) {
                                printf("\n===== ESTANTES DISPONIVEIS =====\n");
                                for (int i = 0; i < numEstantes; i++) {
                                    printf("%d. ", i);
                                    getEstante(estantes[i]);
                                }
                            } else {
                                printf("Nenhuma estante cadastrada!\n");
                            }
                            break;
                            
                        case 3: // Renomear Estante
                            if (numEstantes > 0) {
                                printf("\n===== ESTANTES DISPONIVEIS =====\n");
                                for (int i = 0; i < numEstantes; i++) {
                                    printf("%d. ", i);
                                    getEstante(estantes[i]);
                                }
                                
                                printf("Digite o indice da estante que deseja renomear: ");
                                scanf("%d", &indiceEstante);
                                limparBuffer();
                                
                                if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                    printf("Digite o novo nome da estante: ");
                                    fgets(novoNome, sizeof(novoNome), stdin);
                                    novoNome[strcspn(novoNome, "\n")] = '\0'; // Remover o \n do final
                                    
                                    editarEstante(estantes[indiceEstante], novoNome);
                                    printf("Estante renomeada com sucesso!\n");
                                } else {
                                    printf("Indice invalido!\n");
                                }
                            } else {
                                printf("Nenhuma estante cadastrada!\n");
                            }
                            break;
                            
                        case 4: // Excluir Estante
                            if (numEstantes > 0) {
                                printf("\n===== ESTANTES DISPONIVEIS =====\n");
                                for (int i = 0; i < numEstantes; i++) {
                                    printf("%d. ", i);
                                    getEstante(estantes[i]);
                                }
                                
                                printf("Digite o indice da estante que deseja excluir: ");
                                scanf("%d", &indiceEstante);
                                limparBuffer();
                                
                                if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                    liberarEstante(estantes[indiceEstante]);
                                    
                                    // Reorganizar o array de estantes
                                    for (int i = indiceEstante; i < numEstantes - 1; i++) {
                                        estantes[i] = estantes[i + 1];
                                    }
                                    estantes[numEstantes - 1] = NULL;
                                    numEstantes--;
                                    
                                    printf("Estante excluida com sucesso!\n");
                                } else {
                                    printf("Indice invalido!\n");
                                }
                            } else {
                                printf("Nenhuma estante cadastrada!\n");
                            }
                            break;
                    }
                } while (opcaoEstantes != 5);
                break;
                
            case 2: // Gerenciar Livros
                if (numEstantes == 0) {
                    printf("Nenhuma estante cadastrada! Crie uma estante primeiro.\n");
                    break;
                }
                
                do {
                    exibirMenuLivros();
                    scanf("%d", &opcaoLivros);
                    limparBuffer();
                    
                    switch (opcaoLivros) {
                        case 1: // Adicionar Livro
                            printf("\n===== ESTANTES DISPONIVEIS =====\n");
                            for (int i = 0; i < numEstantes; i++) {
                                printf("%d. ", i);
                                getEstante(estantes[i]);
                            }
                            
                            printf("Digite o indice da estante onde deseja adicionar o livro: ");
                            scanf("%d", &indiceEstante);
                            limparBuffer();
                            
                            if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                printf("Digite o nome do livro: ");
                                fgets(nome, sizeof(nome), stdin);
                                nome[strcspn(nome, "\n")] = '\0';
                                
                                printf("Digite o nome do autor: ");
                                fgets(autor, sizeof(autor), stdin);
                                autor[strcspn(autor, "\n")] = '\0';
                                
                                printf("Digite o numero de paginas: ");
                                scanf("%d", &paginas);
                                
                                printf("Digite o ano de publicacao: ");
                                scanf("%d", &ano);
                                limparBuffer();
                                
                                Tlivro *novoLivro = criarLivro(nome, autor, paginas, ano);
                                if (novoLivro != NULL) {
                                    adicionarLivro(estantes[indiceEstante], novoLivro);
                                    printf("Livro '%s' adicionado com sucesso!\n", nome);
                                } else {
                                    printf("Erro ao criar livro!\n");
                                }
                            } else {
                                printf("Indice invalido!\n");
                            }
                            break;
                            
                        case 2: // Listar Livros de uma Estante
                            printf("\n===== ESTANTES DISPONIVEIS =====\n");
                            for (int i = 0; i < numEstantes; i++) {
                                printf("%d. ", i);
                                getEstante(estantes[i]);
                            }
                            
                            printf("Digite o indice da estante que deseja listar os livros: ");
                            scanf("%d", &indiceEstante);
                            limparBuffer();
                            
                            if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                printf("\n===== LIVROS DA ESTANTE '%s' =====\n", estantes[indiceEstante]->nome);
                                imprimirLivros(estantes[indiceEstante]);
                            } else {
                                printf("Indice invalido!\n");
                            }
                            break;
                            
                        case 3: // Editar Livro
                            printf("\n===== ESTANTES DISPONIVEIS =====\n");
                            for (int i = 0; i < numEstantes; i++) {
                                printf("%d. ", i);
                                getEstante(estantes[i]);
                            }
                            
                            printf("Digite o indice da estante que contem o livro: ");
                            scanf("%d", &indiceEstante);
                            limparBuffer();
                            
                            if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                printf("\n===== LIVROS DA ESTANTE '%s' =====\n", estantes[indiceEstante]->nome);
                                imprimirLivros(estantes[indiceEstante]);
                                
                                printf("Digite o indice do livro que deseja editar: ");
                                scanf("%d", &indiceLivro);
                                limparBuffer();
                                
                                if (indiceLivro >= 0 && indiceLivro < estantes[indiceEstante]->tamanho) {
                                    printf("Digite o novo nome do livro: ");
                                    fgets(nome, sizeof(nome), stdin);
                                    nome[strcspn(nome, "\n")] = '\0';
                                    
                                    printf("Digite o novo nome do autor: ");
                                    fgets(autor, sizeof(autor), stdin);
                                    autor[strcspn(autor, "\n")] = '\0';
                                    
                                    printf("Digite o novo numero de paginas: ");
                                    scanf("%d", &paginas);
                                    
                                    printf("Digite o novo ano de publicacao: ");
                                    scanf("%d", &ano);
                                    limparBuffer();
                                    
                                    editarLivro(estantes[indiceEstante], indiceLivro, nome, autor, paginas, ano);
                                    printf("Livro editado com sucesso!\n");
                                } else {
                                    printf("Indice invalido!\n");
                                }
                            } else {
                                printf("Indice invalido!\n");
                            }
                            break;
                            
                        case 4: // Remover Livro
                            printf("\n===== ESTANTES DISPONIVEIS =====\n");
                            for (int i = 0; i < numEstantes; i++) {
                                printf("%d. ", i);
                                getEstante(estantes[i]);
                            }
                            
                            printf("Digite o indice da estante que contem o livro: ");
                            scanf("%d", &indiceEstante);
                            limparBuffer();
                            
                            if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                printf("\n===== LIVROS DA ESTANTE '%s' =====\n", estantes[indiceEstante]->nome);
                                imprimirLivros(estantes[indiceEstante]);
                                
                                printf("Digite o indice do livro que deseja remover: ");
                                scanf("%d", &indiceLivro);
                                limparBuffer();
                                
                                if (indiceLivro >= 0 && indiceLivro < estantes[indiceEstante]->tamanho) {
                                    removerLivro(estantes[indiceEstante], indiceLivro);
                                    printf("Livro removido com sucesso!\n");
                                } else {
                                    printf("Indice invalido!\n");
                                }
                            } else {
                                printf("Indice invalido!\n");
                            }
                            break;
                            
                        case 5: // Ordenar Livros por Nome
                            printf("\n===== ESTANTES DISPONIVEIS =====\n");
                            for (int i = 0; i < numEstantes; i++) {
                                printf("%d. ", i);
                                getEstante(estantes[i]);
                            }
                            
                            printf("Digite o indice da estante que deseja ordenar os livros: ");
                            scanf("%d", &indiceEstante);
                            limparBuffer();
                            
                            if (indiceEstante >= 0 && indiceEstante < numEstantes) {
                                ordenarEstante(estantes[indiceEstante]);
                                printf("Livros ordenados com sucesso!\n");
                                printf("\n===== LIVROS ORDENADOS DA ESTANTE '%s' =====\n", estantes[indiceEstante]->nome);
                                imprimirLivros(estantes[indiceEstante]);
                            } else {
                                printf("Indice invalido!\n");
                            }
                            break;
                    }
                } while (opcaoLivros != 6);
                break;
                
            case 3: // Buscar Livro
                if (numEstantes == 0) {
                    printf("Nenhuma estante cadastrada! Crie uma estante primeiro.\n");
                    break;
                }
                
                printf("Digite o nome do livro que deseja buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("\n===== RESULTADOS DA BUSCA =====\n");
                int encontrado = 0;
                
                for (int i = 0; i < numEstantes; i++) {
                    printf("Buscando na estante '%s':\n", estantes[i]->nome);
                    for (int j = 0; j < estantes[i]->tamanho; j++) {
                        if (strcmp(estantes[i]->livros[j]->nome, nome) == 0) {
                            printf("Encontrado na estante '%s', indice %d:\n", estantes[i]->nome, j);
                            imprimirLivro(estantes[i]->livros[j]);
                            printf("\n");
                            encontrado = 1;
                        }
                    }
                }
                
                if (!encontrado) {
                    printf("Nenhum livro encontrado com o nome '%s'.\n", nome);
                }
                break;
        }
    } while (opcaoPrincipal != 4);
    
    // Liberar memória alocada
    for (int i = 0; i < numEstantes; i++) {
        if (estantes[i] != NULL) {
            liberarEstante(estantes[i]);
        }
    }
    
    printf("\nPrograma encerrado. Obrigado por utilizar o Sistema de Gerenciamento de Livros e Estantes!\n");
    
    return 0;
}