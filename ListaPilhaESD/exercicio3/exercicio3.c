#include <stdio.h>      // Para funções de entrada/saída padrão (printf, scanf)
#include <stdlib.h>     // Para funções gerais como alocação de memória (malloc, free), números aleatórios (rand, srand)
#include <time.h>       // Para inicializar o gerador de números aleatórios (time)
#include "pilha_carta.h" // Inclui o TAD específico para a pilha de cartas

// --- Funções Auxiliares para o Jogo Paciência ---

/**
 * @brief Retorna a representação em string do valor de uma carta.
 * 
 * @param valor O valor numérico da carta (1-13).
 * @return const char* A string correspondente ("A", "2"-"10", "J", "Q", "K") ou "?" para inválido.
 */
const char* valor_para_string(int valor) {
    // Verifica se o valor está dentro do intervalo válido (1 a 13)
    if (valor >= 2 && valor <= 10) { 
        // Para valores de 2 a 10, precisamos convertê-los para string.
        // Usamos um buffer estático para armazenar a string. Cuidado: não é thread-safe.
        static char buffer[3]; // Buffer para "10" + '\0'
        sprintf(buffer, "%d", valor); // Converte o inteiro para string
        return buffer; // Retorna o ponteiro para o buffer
    }
    // Usa um switch para os valores especiais (Ás, Valete, Dama, Rei)
    switch (valor) {
        case 1:  return "A";  // Ás
        case 11: return "J";  // Valete
        case 12: return "Q";  // Dama
        case 13: return "K";  // Rei
        default: return "?";  // Valor inválido
    }
}

/**
 * @brief Retorna a representação em string (ou caractere Unicode) do naipe de uma carta.
 * 
 * @param naipe O naipe da carta.
 * @return const char* A string/caractere correspondente (Copas, Ouros, Espadas, Paus) ou "?" para inválido.
 */
const char* naipe_para_string(Naipe naipe) {
    // Usa um switch para retornar a string/símbolo do naipe
    switch (naipe) {
        // Usando caracteres Unicode para os naipes (pode não funcionar em todos os terminais)
        case COPAS:   return "♥"; // Coração (Copas)
        case OUROS:   return "♦"; // Diamante (Ouros)
        case ESPADAS: return "♠"; // Espada (Espadas)
        case PAUS:    return "♣"; // Trevo (Paus)
        // Alternativa com letras (se Unicode falhar):
        // case COPAS:   return "C";
        // case OUROS:   return "O";
        // case ESPADAS: return "E";
        // case PAUS:    return "P";
        default:      return "?"; // Naipe inválido
    }
}

/**
 * @brief Imprime uma única carta na tela.
 * Mostra o valor e o naipe se estiver virada para cima, ou "[---]" se virada para baixo.
 * 
 * @param carta A carta a ser impressa.
 */
void imprimir_carta(Carta carta) {
    // Verifica se a carta está virada para cima
    if (carta.virada_para_cima) {
        // Imprime o valor e o naipe da carta usando as funções auxiliares
        printf("[%s%s]", valor_para_string(carta.valor), naipe_para_string(carta.naipe));
    } else {
        // Se a carta estiver virada para baixo, imprime um placeholder
        printf("[---]");
    }
}

/**
 * @brief Imprime o conteúdo de uma pilha de cartas.
 * Útil para visualizar os montes do jogo.
 * 
 * @param p A pilha de cartas a ser impressa.
 * @param nome_pilha O nome da pilha (para identificação na saída).
 */
void imprimir_pilha(const PilhaCarta* p, const char* nome_pilha) {
    // Imprime o nome da pilha
    printf("%s: ", nome_pilha);
    // Verifica se a pilha é válida e não está vazia
    if (!p || pilha_carta_vazia(p)) {
        // Se vazia ou inválida, imprime "(vazia)"
        printf("(vazia)\n");
        return; // Termina a função
    }

    // Para imprimir a pilha do topo para a base (como geralmente vemos), 
    // precisamos acessar os elementos internamente ou usar uma pilha auxiliar.
    // Vamos simular a impressão do topo para simplificar (sem acesso interno).
    Carta topo;
    // Tenta obter a carta do topo
    if (pilha_carta_topo(p, &topo)) {
        // Imprime a carta do topo
        imprimir_carta(topo);
        // Indica que há mais cartas abaixo (se houver)
        if (pilha_carta_tamanho(p) > 1) {
            printf(" (%d cartas)", pilha_carta_tamanho(p));
        }
    }
    printf("\n"); // Nova linha no final
    // OBS: Uma impressão completa exigiria copiar para uma pilha auxiliar e desempilhar/imprimir.
}

/**
 * @brief Cria um baralho padrão de 52 cartas, ordenado.
 * 
 * @return PilhaCarta* Ponteiro para a pilha contendo o baralho ordenado, ou NULL se falhar.
 */
PilhaCarta* criar_baralho_paciencia() {
    // Cria uma pilha com capacidade para 52 cartas
    PilhaCarta* baralho = pilha_carta_criar(52);
    // Verifica se a criação da pilha falhou
    if (!baralho) {
        perror("Erro ao criar pilha para o baralho");
        return NULL; // Retorna NULL em caso de erro
    }

    // Loop pelos 4 naipes (COPAS a PAUS)
    for (Naipe n = COPAS; n <= PAUS; ++n) {
        // Loop pelos 13 valores (1=Ás a 13=Rei)
        for (int v = 1; v <= 13; ++v) {
            // Cria uma nova carta
            Carta c;
            c.valor = v; // Define o valor
            c.naipe = n; // Define o naipe
            c.virada_para_cima = false; // Todas as cartas começam viradas para baixo no baralho
            // Empilha a carta criada no baralho
            if (!pilha_carta_empilhar(baralho, c)) {
                // Se falhar ao empilhar (improvável aqui, mas bom verificar)
                fprintf(stderr, "Erro ao empilhar carta no baralho!\n");
                pilha_carta_destruir(&baralho); // Destrói a pilha parcialmente criada
                return NULL; // Retorna NULL
            }
        }
    }
    // Retorna o ponteiro para o baralho completo e ordenado
    return baralho;
}

/**
 * @brief Embaralha uma pilha de cartas usando o algoritmo Fisher-Yates.
 * 
 * @param p Ponteiro para a pilha de cartas a ser embaralhada.
 * @return true Se o embaralhamento foi bem-sucedido, false caso contrário.
 */
bool embaralhar_pilha(PilhaCarta* p) {
    // Verifica se a pilha é válida
    if (!p) return false;
    // Obtém o número de cartas na pilha
    int n = pilha_carta_tamanho(p);
    // Se a pilha tem 1 ou 0 cartas, não há o que embaralhar
    if (n <= 1) return true; 

    // 1. Copia as cartas da pilha para um array temporário
    Carta* temp_array = (Carta*)malloc(n * sizeof(Carta));
    // Verifica se a alocação do array falhou
    if (!temp_array) {
        perror("Erro ao alocar array temporário para embaralhar");
        return false; // Retorna falha
    }
    // Desempilha todas as cartas da pilha original e armazena no array
    for (int i = 0; i < n; ++i) {
        // É crucial verificar se o desempilhamento funciona
        if (!pilha_carta_desempilhar(p, &temp_array[i])) {
             fprintf(stderr, "Erro ao desempilhar para array temporário!\n");
             free(temp_array); // Libera o array
             // Idealmente, deveríamos tentar reconstruir a pilha original aqui
             return false;
        }
    }
    // Neste ponto, a pilha 'p' está vazia.

    // 2. Embaralha o array usando Fisher-Yates
    // srand(time(NULL)); // Inicializa o gerador de números aleatórios (melhor fazer isso uma vez no main)
    for (int i = n - 1; i > 0; --i) {
        // Gera um índice aleatório 'j' entre 0 e i (inclusive)
        int j = rand() % (i + 1);
        // Troca os elementos nas posições i e j do array
        Carta temp = temp_array[i];
        temp_array[i] = temp_array[j];
        temp_array[j] = temp;
    }

    // 3. Empilha as cartas do array embaralhado de volta na pilha original
    for (int i = 0; i < n; ++i) {
        // Empilha a carta do array de volta na pilha 'p'
        if (!pilha_carta_empilhar(p, temp_array[i])) {
            fprintf(stderr, "Erro ao empilhar de volta após embaralhar!\n");
            free(temp_array); // Libera o array
            // A pilha 'p' está em um estado inconsistente aqui.
            return false;
        }
    }

    // Libera a memória do array temporário
    free(temp_array);
    // Retorna sucesso
    return true;
}

// --- Função Principal (main) ---

int main() {
    // Inicializa o gerador de números aleatórios uma vez no início
    srand(time(NULL));

    // 1. Cria e embaralha o baralho principal
    PilhaCarta* baralho_principal = criar_baralho_paciencia();
    if (!baralho_principal) {
        return 1; // Sai se a criação do baralho falhar
    }
    if (!embaralhar_pilha(baralho_principal)) {
        fprintf(stderr, "Erro ao embaralhar o baralho principal.\n");
        pilha_carta_destruir(&baralho_principal);
        return 1;
    }

    // 2. Cria as pilhas do jogo
    PilhaCarta* estoque = pilha_carta_criar(52); // Capacidade máxima
    PilhaCarta* descarte = pilha_carta_criar(52);
    PilhaCarta* fundacao[4]; // 4 pilhas de fundação
    PilhaCarta* tableau[7];  // 7 pilhas do tableau

    // Verifica se a criação das pilhas de estoque e descarte falhou
    if (!estoque || !descarte) {
        perror("Erro ao criar pilha de estoque ou descarte");
        pilha_carta_destruir(&baralho_principal);
        if (estoque) pilha_carta_destruir(&estoque);
        if (descarte) pilha_carta_destruir(&descarte);
        return 1;
    }

    // Cria as pilhas de fundação
    for (int i = 0; i < 4; ++i) {
        fundacao[i] = pilha_carta_criar(13); // Cada fundação vai de Ás a Rei (13 cartas)
        if (!fundacao[i]) {
            perror("Erro ao criar pilha de fundação");
            // Limpeza das pilhas já criadas
            pilha_carta_destruir(&baralho_principal);
            pilha_carta_destruir(&estoque);
            pilha_carta_destruir(&descarte);
            for (int j = 0; j < i; ++j) pilha_carta_destruir(&fundacao[j]);
            return 1;
        }
    }

    // Cria as pilhas do tableau
    for (int i = 0; i < 7; ++i) {
        // A capacidade precisa ser suficiente para as cartas iniciais + possíveis cartas movidas
        // 52 é seguro, mas (i+1) + 13 (pior caso de Rei a Ás) também funcionaria
        tableau[i] = pilha_carta_criar(52);
        if (!tableau[i]) {
            perror("Erro ao criar pilha do tableau");
            // Limpeza extensiva
            pilha_carta_destruir(&baralho_principal);
            pilha_carta_destruir(&estoque);
            pilha_carta_destruir(&descarte);
            for (int j = 0; j < 4; ++j) pilha_carta_destruir(&fundacao[j]);
            for (int j = 0; j < i; ++j) pilha_carta_destruir(&tableau[j]);
            return 1;
        }
    }

    // 3. Distribui as cartas do baralho para o tableau
    for (int i = 0; i < 7; ++i) { // Para cada pilha do tableau
        for (int j = 0; j <= i; ++j) { // Distribui j+1 cartas
            Carta carta_atual;
            // Tenta desempilhar do baralho principal
            if (!pilha_carta_desempilhar(baralho_principal, &carta_atual)) {
                fprintf(stderr, "Erro: Baralho principal ficou vazio inesperadamente durante a distribuição.\n");
                // Limpeza geral em caso de erro
                pilha_carta_destruir(&baralho_principal);
                pilha_carta_destruir(&estoque);
                pilha_carta_destruir(&descarte);
                for(int k=0; k<4; ++k) pilha_carta_destruir(&fundacao[k]);
                for(int k=0; k<7; ++k) pilha_carta_destruir(&tableau[k]);
                return 1;
            }
            // A última carta de cada pilha do tableau (j == i) é virada para cima
            if (j == i) {
                carta_atual.virada_para_cima = true;
            } else {
                carta_atual.virada_para_cima = false;
            }
            // Empilha a carta na pilha do tableau correspondente
            if (!pilha_carta_empilhar(tableau[i], carta_atual)) {
                 fprintf(stderr, "Erro ao empilhar carta no tableau %d.\n", i);
                 // Limpeza geral
                 // ... (código de limpeza omitido por brevidade, mas necessário)
                 return 1;
            }
        }
    }

    // 4. Coloca as cartas restantes no estoque
    while (!pilha_carta_vazia(baralho_principal)) {
        Carta carta_restante;
        pilha_carta_desempilhar(baralho_principal, &carta_restante); // Pega a carta do topo do que sobrou
        carta_restante.virada_para_cima = false; // Cartas no estoque ficam viradas para baixo
        if (!pilha_carta_empilhar(estoque, carta_restante)) {
            fprintf(stderr, "Erro ao empilhar carta no estoque.\n");
            // Limpeza geral
            // ... (código de limpeza omitido por brevidade, mas necessário)
            return 1;
        }
    }
    // O baralho principal agora está vazio e pode ser destruído
    pilha_carta_destruir(&baralho_principal);

    // --- Loop Principal do Jogo ---
    printf("--- Jogo de Paciência Iniciado ---\n\n");
    bool jogo_terminado = false;
    char comando;

    while (!jogo_terminado) {
        // 1. Imprime o estado atual do jogo
        printf("\n----------------------------------------\n");
        printf("Estoque: %d cartas | ", pilha_carta_tamanho(estoque));
        imprimir_pilha(descarte, "Descarte");
        printf("Fundações:\n");
        for (int i = 0; i < 4; ++i) {
            char nome_fund[15];
            sprintf(nome_fund, "  F%d", i + 1);
            imprimir_pilha(fundacao[i], nome_fund);
        }
        printf("Tableau:\n");
        for (int i = 0; i < 7; ++i) {
            char nome_tab[15];
            sprintf(nome_tab, "  T%d", i + 1);
            // TODO: Melhorar a impressão do tableau para mostrar todas as cartas visíveis
            imprimir_pilha(tableau[i], nome_tab);
        }
        printf("----------------------------------------\n");

        // 2. Solicita o comando do jogador
        printf("Comandos: (D)esenhar do estoque, (M)over, (S)air\n");
        printf("Digite o comando: ");
        // Lê apenas um caractere e o caractere de nova linha
        if (scanf(" %c", &comando) != 1) {
            // Limpa buffer em caso de erro de leitura
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Comando inválido. Tente novamente.\n");
            continue; // Volta ao início do loop
        }
        // Limpa o restante da linha (caso o usuário digite mais de um caractere)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // 3. Processa o comando
        switch (comando) {
            case 'd':
            case 'D':
                printf("Ação: Desenhar do estoque...\n");
                // Verifica se o estoque está vazio
                if (pilha_carta_vazia(estoque)) {
                    printf("Estoque vazio. Reabastecendo do descarte...\n");
                    // Move todas as cartas do descarte de volta para o estoque
                    while (!pilha_carta_vazia(descarte)) {
                        Carta carta_movida;
                        if (pilha_carta_desempilhar(descarte, &carta_movida)) {
                            carta_movida.virada_para_cima = false; // Vira para baixo no estoque
                            if (!pilha_carta_empilhar(estoque, carta_movida)) {
                                fprintf(stderr, "Erro crítico ao reabastecer estoque!\n");
                                // Idealmente, tratar o erro de forma mais robusta
                                jogo_terminado = true; // Termina o jogo em caso de erro grave
                                break;
                            }
                        } else {
                             fprintf(stderr, "Erro ao desempilhar do descarte para reabastecer estoque.\n");
                             jogo_terminado = true;
                             break;
                        }
                    }
                    if(jogo_terminado) break; // Sai do switch se ocorreu erro
                    printf("Estoque reabastecido.");
                } else {
                    // Move uma carta do estoque para o descarte
                    Carta carta_desenhada;
                    if (pilha_carta_desempilhar(estoque, &carta_desenhada)) {
                        carta_desenhada.virada_para_cima = true; // Vira para cima no descarte
                        if (!pilha_carta_empilhar(descarte, carta_desenhada)) {
                            fprintf(stderr, "Erro ao empilhar no descarte!\n");
                            // Tenta devolver a carta ao estoque em caso de erro
                            carta_desenhada.virada_para_cima = false;
                            pilha_carta_empilhar(estoque, carta_desenhada);
                            // Não termina o jogo, mas avisa do erro
                        } else {
                            printf("Carta desenhada: ");
                            imprimir_carta(carta_desenhada);
                            printf("\n");
                        }
                    } else {
                        fprintf(stderr, "Erro ao desempilhar do estoque.\n");
                        // Erro inesperado, estoque não estava vazio mas falhou
                    }
                }
                break;
            case 'm':
            case 'M':
                printf("Ação: Mover carta(s)...\n");
                char origem_str[5], destino_str[5]; // Buffers para ler a origem e destino (ex: T1, F2, D)
                printf("Mover de (ex: D, T1..T7, F1..F4): ");
                if (scanf("%4s", origem_str) != 1) {
                    // Limpa buffer
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada de origem inválida.\n");
                    break;
                }
                printf("Mover para (ex: T1..T7, F1..F4): ");
                if (scanf("%4s", destino_str) != 1) {
                    // Limpa buffer
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada de destino inválida.\n");
                    break;
                }
                // Limpa o restante da linha do buffer de entrada
                int c; while ((c = getchar()) != '\n' && c != EOF);

                // Analisa as strings de origem e destino
                int indice_origem = -1, indice_destino = -1;
                PilhaCarta* p_origem = parse_pilha_origem(origem_str, descarte, tableau, fundacao, &indice_origem);
                PilhaCarta* p_destino = parse_pilha_destino(destino_str, tableau, fundacao, &indice_destino);

                if (!p_origem) {
                    printf("Pilha de origem '%s' inválida.\n", origem_str);
                    break;
                }
                if (!p_destino) {
                    printf("Pilha de destino '%s' inválida.\n", destino_str);
                    break;
                }
                if (p_origem == p_destino) {
                    printf("Origem e destino não podem ser a mesma pilha.\n");
                    break;
                }

                printf("Tentando mover de %s para %s...\n", origem_str, destino_str);

                // --- Lógica de Movimentação (Implementação Parcial) ---

                // 1. Verificar se a origem está vazia
                if (pilha_carta_vazia(p_origem)) {
                    printf("Erro: A pilha de origem está vazia.\n");
                    break;
                }

                // 2. Obter a(s) carta(s) a mover e validar
                Carta carta_topo_origem;
                pilha_carta_topo(p_origem, &carta_topo_origem); // Apenas consulta por enquanto

+               // Verifica se a carta do topo da origem está virada para cima (necessário para mover)
+               // Exceção: Mover da pilha de descarte (sempre virada para cima)
+               if (p_origem != descarte && !carta_topo_origem.virada_para_cima) {
+               printf("Erro: Não pode mover carta(s) virada(s) para baixo do tableau.\n");
+               break;
+               }
+
                // TODO: Lógica mais complexa para mover múltiplas cartas do tableau
                // TODO: Implementar validação usando pode_mover_para_fundacao e pode_mover_para_tableau

                // Exemplo básico: Mover 1 carta do topo (se for válida)
                bool movimento_valido = false;
                // Verifica se o destino é uma fundação
                if (toupper(destino_str[0]) == 'F') {
                    // movimento_valido = pode_mover_para_fundacao(carta_topo_origem, p_destino);
                    printf("Validação para fundação (não implementada)\n"); // Placeholder
                }
                // Verifica se o destino é um tableau
                else if (toupper(destino_str[0]) == 'T') {
                    // movimento_valido = pode_mover_para_tableau(carta_topo_origem, p_destino);
                     printf("Validação para tableau (não implementada)\n"); // Placeholder
                }

                // 3. Executar o movimento (se válido)
                if (movimento_valido) {
                    printf("Movimento válido! Executando...\n");
                    // Desempilha da origem
                    if (!pilha_carta_desempilhar(p_origem, &carta_topo_origem)) {
                        fprintf(stderr, "Erro crítico ao desempilhar da origem após validação!\n");
                        break; // Algo deu muito errado
                    }
                    // Empilha no destino
                    if (!pilha_carta_empilhar(p_destino, carta_topo_origem)) {
                        fprintf(stderr, "Erro crítico ao empilhar no destino após validação!\n");
                        // Tenta devolver para a origem para manter consistência
                        pilha_carta_empilhar(p_origem, carta_topo_origem);
                        break; // Algo deu muito errado
                    }

                    printf("Carta movida: ");
                    imprimir_carta(carta_topo_origem);
                    printf(" para %s\n", destino_str);

                    // Se moveu DO tableau e a pilha de origem não ficou vazia,
                    // verifica se a nova carta do topo precisa ser virada.
                    if (toupper(origem_str[0]) == 'T' && !pilha_carta_vazia(p_origem)) {
                        Carta nova_topo_origem;
                        // Consulta a nova carta do topo da origem
                        if (pilha_carta_topo(p_origem, &nova_topo_origem)) {
                            if (!nova_topo_origem.virada_para_cima) {
                                printf("Virando a próxima carta em %s...\n", origem_str);
                                // Para virar: desempilha, modifica, empilha de volta
                                if (pilha_carta_desempilhar(p_origem, &nova_topo_origem)) {
                                    nova_topo_origem.virada_para_cima = true;
                                    if (!pilha_carta_empilhar(p_origem, nova_topo_origem)) {
                                        fprintf(stderr, "Erro crítico ao re-empilhar carta virada em %s!\n", origem_str);
                                    }
                                } else {
                                     fprintf(stderr, "Erro ao desempilhar para virar carta em %s!\n", origem_str);
                                }
                            }
                        } else {
                             fprintf(stderr, "Erro ao consultar topo de %s após mover carta.\n", origem_str);
                        }
                    }

                } else {
                    printf("Movimento inválido! Verifique as regras do Paciência.\n");
                }

                break;
            case 's':
            case 'S':
                printf("Saindo do jogo...\n");
                jogo_terminado = true;
                break;
            default:
                printf("Comando desconhecido: '%c'\n", comando);
                break;
        }

        // 4. Verifica condição de vitória (placeholder)
        // if (todas_fundacoes_completas) {
        //     printf("Parabéns, você venceu!\n");
        //     jogo_terminado = true;
        // }
        if (verificar_vitoria(fundacao)) {
            printf("\n****************************************\n");
            printf("*** PARABÉNS! VOCÊ VENCEU O JOGO! ***\n");
            printf("****************************************\n");
            jogo_terminado = true;
        }
    }

    // --- Limpeza Final --- 
    // Destrói todas as pilhas criadas para o jogo
    pilha_carta_destruir(&estoque);
    pilha_carta_destruir(&descarte);
    for (int i = 0; i < 4; ++i) {
        pilha_carta_destruir(&fundacao[i]);
    }
    for (int i = 0; i < 7; ++i) {
        pilha_carta_destruir(&tableau[i]);
    }

    return 0; // Indica que o programa (setup) terminou com sucesso
}


// --- Funções Auxiliares para Movimentação ---

/**
 * @brief Analisa a string de origem e retorna o ponteiro para a pilha correspondente.
 *
 * @param origem_str A string de entrada (ex: "D", "T1", "F3").
 * @param descarte Ponteiro para a pilha de descarte.
 * @param tableau Array de ponteiros para as pilhas do tableau.
 * @param fundacao Array de ponteiros para as pilhas de fundação.
 * @param indice_pilha Ponteiro para armazenar o índice da pilha (para tableau/fundacao).
 * @return PilhaCarta* Ponteiro para a pilha de origem ou NULL se inválida.
 */
PilhaCarta* parse_pilha_origem(const char* origem_str, PilhaCarta* descarte, PilhaCarta* tableau[], PilhaCarta* fundacao[], int* indice_pilha) {
    if (!origem_str || !indice_pilha) return NULL;
    *indice_pilha = -1; // Valor padrão

    if (toupper(origem_str[0]) == 'D' && origem_str[1] == '\0') {
        return descarte;
    } else if (toupper(origem_str[0]) == 'T' && origem_str[1] >= '1' && origem_str[1] <= '7' && origem_str[2] == '\0') {
        *indice_pilha = origem_str[1] - '1'; // Converte '1'.. '7' para 0..6
        return tableau[*indice_pilha];
    } else if (toupper(origem_str[0]) == 'F' && origem_str[1] >= '1' && origem_str[1] <= '4' && origem_str[2] == '\0') {
        *indice_pilha = origem_str[1] - '1'; // Converte '1'.. '4' para 0..3
        // Geralmente não se move DA fundação, mas incluído para análise completa
        return fundacao[*indice_pilha];
    }
    return NULL; // Origem inválida
}

/**
 * @brief Analisa a string de destino e retorna o ponteiro para a pilha correspondente.
 *
 * @param destino_str A string de entrada (ex: "T1", "F3").
 * @param tableau Array de ponteiros para as pilhas do tableau.
 * @param fundacao Array de ponteiros para as pilhas de fundação.
 * @param indice_pilha Ponteiro para armazenar o índice da pilha (para tableau/fundacao).
 * @return PilhaCarta* Ponteiro para a pilha de destino ou NULL se inválida.
 */
PilhaCarta* parse_pilha_destino(const char* destino_str, PilhaCarta* tableau[], PilhaCarta* fundacao[], int* indice_pilha) {
     if (!destino_str || !indice_pilha) return NULL;
    *indice_pilha = -1; // Valor padrão

    if (toupper(destino_str[0]) == 'T' && destino_str[1] >= '1' && destino_str[1] <= '7' && destino_str[2] == '\0') {
        *indice_pilha = destino_str[1] - '1'; // Converte '1'.. '7' para 0..6
        return tableau[*indice_pilha];
    } else if (toupper(destino_str[0]) == 'F' && destino_str[1] >= '1' && destino_str[1] <= '4' && destino_str[2] == '\0') {
        *indice_pilha = destino_str[1] - '1'; // Converte '1'.. '4' para 0..3
        return fundacao[*indice_pilha];
    }
    return NULL; // Destino inválido (não pode mover para Descarte ou Estoque)
}

// Função auxiliar para determinar a cor de uma carta (true para vermelho, false para preto)
bool eh_vermelha(Naipe naipe) {
    return naipe == COPAS || naipe == OUROS;
}

/**
 * @brief Verifica se uma carta pode ser movida para uma pilha de fundação.
 *
 * @param carta_movida A carta que se deseja mover.
 * @param pilha_fundacao A pilha de fundação de destino.
 * @return true Se o movimento for válido, false caso contrário.
 */
bool pode_mover_para_fundacao(Carta carta_movida, const PilhaCarta* pilha_fundacao) {
    if (!pilha_fundacao) return false; // Destino inválido

    if (pilha_carta_vazia(pilha_fundacao)) {
        // Só pode mover um Ás (valor 1) para uma fundação vazia
        return carta_movida.valor == 1;
    } else {
        // Se não estiver vazia, obtém a carta do topo
        Carta topo_fundacao;
        if (!pilha_carta_topo(pilha_fundacao, &topo_fundacao)) {
            return false; // Erro ao obter o topo
        }
        // A carta movida deve ser do mesmo naipe e ter valor 1 a mais que o topo
        return carta_movida.naipe == topo_fundacao.naipe && carta_movida.valor == topo_fundacao.valor + 1;
    }
}

/**
 * @brief Verifica se uma carta pode ser movida para uma pilha do tableau.
 *
 * @param carta_movida A carta que se deseja mover (a primeira da sequência, se for o caso).
 * @param pilha_tableau A pilha do tableau de destino.
 * @return true Se o movimento for válido, false caso contrário.
 */
bool pode_mover_para_tableau(Carta carta_movida, const PilhaCarta* pilha_tableau) {
    if (!pilha_tableau) return false; // Destino inválido

    // A carta a ser movida DEVE estar virada para cima (verificação feita antes de chamar)
    // if (!carta_movida.virada_para_cima) return false;

    if (pilha_carta_vazia(pilha_tableau)) {
        // Só pode mover um Rei (valor 13) para um tableau vazio
        return carta_movida.valor == 13;
    } else {
        // Se não estiver vazio, obtém a carta do topo
        Carta topo_tableau;
        if (!pilha_carta_topo(pilha_tableau, &topo_tableau)) {
            return false; // Erro ao obter o topo
        }
        // A carta no topo do destino DEVE estar virada para cima
        if (!topo_tableau.virada_para_cima) {
            return false; // Não pode colocar sobre carta virada para baixo
        }
        // A carta movida deve ter cor oposta e valor 1 a menos que o topo
        bool cor_movida_vermelha = eh_vermelha(carta_movida.naipe);
        bool cor_topo_vermelha = eh_vermelha(topo_tableau.naipe);

        return cor_movida_vermelha != cor_topo_vermelha && carta_movida.valor == topo_tableau.valor - 1;
    }
}

/**
 * @brief Encontra o índice da primeira carta (mais próxima da base) que está virada para cima em uma pilha do tableau.
 *        Útil para determinar qual sequência pode ser movida.
 *
 * @param pilha_tableau A pilha do tableau a ser verificada.
 * @return int O índice da primeira carta virada para cima (0 a N-1), ou -1 se nenhuma estiver virada ou a pilha for inválida/vazia.
 */
int encontrar_primeira_carta_virada(const PilhaCarta* pilha_tableau) {
    if (!pilha_tableau || pilha_carta_vazia(pilha_tableau)) {
        return -1;
    }

    // O TAD Pilha Sequencial não expõe acesso direto aos dados por índice.
    // Precisamos usar uma pilha auxiliar para verificar as cartas da base para o topo.
    PilhaCarta* aux = pilha_carta_criar(pilha_carta_tamanho(pilha_tableau));
    if (!aux) return -1; // Falha ao criar pilha auxiliar

    int indice_encontrado = -1;
    int indice_atual = 0;
    Carta temp;

    // 1. Mover tudo para a pilha auxiliar (inverte a ordem)
    while (pilha_carta_desempilhar((PilhaCarta*)pilha_tableau, &temp)) { // Cast necessário pois a função original não é const
        pilha_carta_empilhar(aux, temp);
    }

    // 2. Verificar da base (topo da aux) para o topo (base da aux)
    while (pilha_carta_desempilhar(aux, &temp)) {
        if (temp.virada_para_cima && indice_encontrado == -1) {
            indice_encontrado = indice_atual;
            // Não paramos aqui, precisamos restaurar a pilha original
        }
        // 3. Restaurar a pilha original
        pilha_carta_empilhar((PilhaCarta*)pilha_tableau, temp); // Cast necessário
        indice_atual++;
    }

    pilha_carta_destruir(&aux);
    return indice_encontrado;
}


// --- Fim das Funções Auxiliares para Movimentação ---


int main() {
    // Inicializa o gerador de números aleatórios uma vez no início
    srand(time(NULL));

    // 1. Cria e embaralha o baralho principal
    PilhaCarta* baralho_principal = criar_baralho_paciencia();
    if (!baralho_principal) {
        return 1; // Sai se a criação do baralho falhar
    }
    if (!embaralhar_pilha(baralho_principal)) {
        fprintf(stderr, "Erro ao embaralhar o baralho principal.\n");
        pilha_carta_destruir(&baralho_principal);
        return 1;
    }

    // 2. Cria as pilhas do jogo
    PilhaCarta* estoque = pilha_carta_criar(52); // Capacidade máxima
    PilhaCarta* descarte = pilha_carta_criar(52);
    PilhaCarta* fundacao[4]; // 4 pilhas de fundação
    PilhaCarta* tableau[7];  // 7 pilhas do tableau

    // Verifica se a criação das pilhas de estoque e descarte falhou
    if (!estoque || !descarte) {
        perror("Erro ao criar pilha de estoque ou descarte");
        pilha_carta_destruir(&baralho_principal);
        if (estoque) pilha_carta_destruir(&estoque);
        if (descarte) pilha_carta_destruir(&descarte);
        return 1;
    }

    // Cria as pilhas de fundação
    for (int i = 0; i < 4; ++i) {
        fundacao[i] = pilha_carta_criar(13); // Cada fundação vai de Ás a Rei (13 cartas)
        if (!fundacao[i]) {
            perror("Erro ao criar pilha de fundação");
            // Limpeza das pilhas já criadas
            pilha_carta_destruir(&baralho_principal);
            pilha_carta_destruir(&estoque);
            pilha_carta_destruir(&descarte);
            for (int j = 0; j < i; ++j) pilha_carta_destruir(&fundacao[j]);
            return 1;
        }
    }

    // Cria as pilhas do tableau
    for (int i = 0; i < 7; ++i) {
        // A capacidade precisa ser suficiente para as cartas iniciais + possíveis cartas movidas
        // 52 é seguro, mas (i+1) + 13 (pior caso de Rei a Ás) também funcionaria
        tableau[i] = pilha_carta_criar(52);
        if (!tableau[i]) {
            perror("Erro ao criar pilha do tableau");
            // Limpeza extensiva
            pilha_carta_destruir(&baralho_principal);
            pilha_carta_destruir(&estoque);
            pilha_carta_destruir(&descarte);
            for (int j = 0; j < 4; ++j) pilha_carta_destruir(&fundacao[j]);
            for (int j = 0; j < i; ++j) pilha_carta_destruir(&tableau[j]);
            return 1;
        }
    }

    // 3. Distribui as cartas do baralho para o tableau
    for (int i = 0; i < 7; ++i) { // Para cada pilha do tableau
        for (int j = 0; j <= i; ++j) { // Distribui j+1 cartas
            Carta carta_atual;
            // Tenta desempilhar do baralho principal
            if (!pilha_carta_desempilhar(baralho_principal, &carta_atual)) {
                fprintf(stderr, "Erro: Baralho principal ficou vazio inesperadamente durante a distribuição.\n");
                // Limpeza geral em caso de erro
                pilha_carta_destruir(&baralho_principal);
                pilha_carta_destruir(&estoque);
                pilha_carta_destruir(&descarte);
                for(int k=0; k<4; ++k) pilha_carta_destruir(&fundacao[k]);
                for(int k=0; k<7; ++k) pilha_carta_destruir(&tableau[k]);
                return 1;
            }
            // A última carta de cada pilha do tableau (j == i) é virada para cima
            if (j == i) {
                carta_atual.virada_para_cima = true;
            } else {
                carta_atual.virada_para_cima = false;
            }
            // Empilha a carta na pilha do tableau correspondente
            if (!pilha_carta_empilhar(tableau[i], carta_atual)) {
                 fprintf(stderr, "Erro ao empilhar carta no tableau %d.\n", i);
                 // Limpeza geral
                 // ... (código de limpeza omitido por brevidade, mas necessário)
                 return 1;
            }
        }
    }

    // 4. Coloca as cartas restantes no estoque
    while (!pilha_carta_vazia(baralho_principal)) {
        Carta carta_restante;
        pilha_carta_desempilhar(baralho_principal, &carta_restante); // Pega a carta do topo do que sobrou
        carta_restante.virada_para_cima = false; // Cartas no estoque ficam viradas para baixo
        if (!pilha_carta_empilhar(estoque, carta_restante)) {
            fprintf(stderr, "Erro ao empilhar carta no estoque.\n");
            // Limpeza geral
            // ... (código de limpeza omitido por brevidade, mas necessário)
            return 1;
        }
    }
    // O baralho principal agora está vazio e pode ser destruído
    pilha_carta_destruir(&baralho_principal);

    // --- Loop Principal do Jogo ---
    printf("--- Jogo de Paciência Iniciado ---\n\n");
    bool jogo_terminado = false;
    char comando;

    while (!jogo_terminado) {
        // 1. Imprime o estado atual do jogo
        printf("\n----------------------------------------\n");
        printf("Estoque: %d cartas | ", pilha_carta_tamanho(estoque));
        imprimir_pilha(descarte, "Descarte");
        printf("Fundações:\n");
        for (int i = 0; i < 4; ++i) {
            char nome_fund[15];
            sprintf(nome_fund, "  F%d", i + 1);
            imprimir_pilha(fundacao[i], nome_fund);
        }
        printf("Tableau:\n");
        for (int i = 0; i < 7; ++i) {
            char nome_tab[15];
            sprintf(nome_tab, "  T%d", i + 1);
            // TODO: Melhorar a impressão do tableau para mostrar todas as cartas visíveis
            imprimir_pilha(tableau[i], nome_tab);
        }
        printf("----------------------------------------\n");

        // 2. Solicita o comando do jogador
        printf("Comandos: (D)esenhar do estoque, (M)over, (S)air\n");
        printf("Digite o comando: ");
        // Lê apenas um caractere e o caractere de nova linha
        if (scanf(" %c", &comando) != 1) {
            // Limpa buffer em caso de erro de leitura
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Comando inválido. Tente novamente.\n");
            continue; // Volta ao início do loop
        }
        // Limpa o restante da linha (caso o usuário digite mais de um caractere)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // 3. Processa o comando
        switch (comando) {
            case 'd':
            case 'D':
                printf("Ação: Desenhar do estoque...\n");
                // Verifica se o estoque está vazio
                if (pilha_carta_vazia(estoque)) {
                    printf("Estoque vazio. Reabastecendo do descarte...\n");
                    // Move todas as cartas do descarte de volta para o estoque
                    while (!pilha_carta_vazia(descarte)) {
                        Carta carta_movida;
                        if (pilha_carta_desempilhar(descarte, &carta_movida)) {
                            carta_movida.virada_para_cima = false; // Vira para baixo no estoque
                            if (!pilha_carta_empilhar(estoque, carta_movida)) {
                                fprintf(stderr, "Erro crítico ao reabastecer estoque!\n");
                                // Idealmente, tratar o erro de forma mais robusta
                                jogo_terminado = true; // Termina o jogo em caso de erro grave
                                break;
                            }
                        } else {
                             fprintf(stderr, "Erro ao desempilhar do descarte para reabastecer estoque.\n");
                             jogo_terminado = true;
                             break;
                        }
                    }
                    if(jogo_terminado) break; // Sai do switch se ocorreu erro
                    printf("Estoque reabastecido.");
                } else {
                    // Move uma carta do estoque para o descarte
                    Carta carta_desenhada;
                    if (pilha_carta_desempilhar(estoque, &carta_desenhada)) {
                        carta_desenhada.virada_para_cima = true; // Vira para cima no descarte
                        if (!pilha_carta_empilhar(descarte, carta_desenhada)) {
                            fprintf(stderr, "Erro ao empilhar no descarte!\n");
                            // Tenta devolver a carta ao estoque em caso de erro
                            carta_desenhada.virada_para_cima = false;
                            pilha_carta_empilhar(estoque, carta_desenhada);
                            // Não termina o jogo, mas avisa do erro
                        } else {
                            printf("Carta desenhada: ");
                            imprimir_carta(carta_desenhada);
                            printf("\n");
                        }
                    } else {
                        fprintf(stderr, "Erro ao desempilhar do estoque.\n");
                        // Erro inesperado, estoque não estava vazio mas falhou
                    }
                }
                break;
            case 'm':
            case 'M':
                printf("Ação: Mover carta(s)...\n");
                char origem_str[5], destino_str[5]; // Buffers para ler a origem e destino (ex: T1, F2, D)
                printf("Mover de (ex: D, T1..T7, F1..F4): ");
                if (scanf("%4s", origem_str) != 1) {
                    // Limpa buffer
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada de origem inválida.\n");
                    break;
                }
                printf("Mover para (ex: T1..T7, F1..F4): ");
                if (scanf("%4s", destino_str) != 1) {
                    // Limpa buffer
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada de destino inválida.\n");
                    break;
                }
                // Limpa o restante da linha do buffer de entrada
                int c; while ((c = getchar()) != '\n' && c != EOF);

                // Analisa as strings de origem e destino
                int indice_origem = -1, indice_destino = -1;
                PilhaCarta* p_origem = parse_pilha_origem(origem_str, descarte, tableau, fundacao, &indice_origem);
                PilhaCarta* p_destino = parse_pilha_destino(destino_str, tableau, fundacao, &indice_destino);

                if (!p_origem) {
                    printf("Pilha de origem '%s' inválida.\n", origem_str);
                    break;
                }
                if (!p_destino) {
                    printf("Pilha de destino '%s' inválida.\n", destino_str);
                    break;
                }
                if (p_origem == p_destino) {
                    printf("Origem e destino não podem ser a mesma pilha.\n");
                    break;
                }

                printf("Tentando mover de %s para %s...\n", origem_str, destino_str);

                // --- Lógica de Movimentação (Implementação Parcial) ---

                // 1. Verificar se a origem está vazia
                if (pilha_carta_vazia(p_origem)) {
                    printf("Erro: A pilha de origem está vazia.\n");
                    break;
                }

                // 2. Obter a(s) carta(s) a mover e validar
                Carta carta_topo_origem;
                pilha_carta_topo(p_origem, &carta_topo_origem); // Apenas consulta por enquanto

+               // Verifica se a carta do topo da origem está virada para cima (necessário para mover)
+               // Exceção: Mover da pilha de descarte (sempre virada para cima)
+               if (p_origem != descarte && !carta_topo_origem.virada_para_cima) {
+               printf("Erro: Não pode mover carta(s) virada(s) para baixo do tableau.\n");
+               break;
+               }
+
                // TODO: Lógica mais complexa para mover múltiplas cartas do tableau
                // TODO: Implementar validação usando pode_mover_para_fundacao e pode_mover_para_tableau

                // Exemplo básico: Mover 1 carta do topo (se for válida)
                bool movimento_valido = false;
                // Verifica se o destino é uma fundação
                if (toupper(destino_str[0]) == 'F') {
                    // movimento_valido = pode_mover_para_fundacao(carta_topo_origem, p_destino);
                    printf("Validação para fundação (não implementada)\n"); // Placeholder
                }
                // Verifica se o destino é um tableau
                else if (toupper(destino_str[0]) == 'T') {
                    // movimento_valido = pode_mover_para_tableau(carta_topo_origem, p_destino);
                     printf("Validação para tableau (não implementada)\n"); // Placeholder
                }

                // 3. Executar o movimento (se válido)
                if (movimento_valido) {
                    printf("Movimento válido! Executando...\n");
                    // Desempilha da origem
                    if (!pilha_carta_desempilhar(p_origem, &carta_topo_origem)) {
                        fprintf(stderr, "Erro crítico ao desempilhar da origem após validação!\n");
                        break; // Algo deu muito errado
                    }
                    // Empilha no destino
                    if (!pilha_carta_empilhar(p_destino, carta_topo_origem)) {
                        fprintf(stderr, "Erro crítico ao empilhar no destino após validação!\n");
                        // Tenta devolver para a origem para manter consistência
                        pilha_carta_empilhar(p_origem, carta_topo_origem);
                        break; // Algo deu muito errado
                    }

                    printf("Carta movida: ");
                    imprimir_carta(carta_topo_origem);
                    printf(" para %s\n", destino_str);

                    // Se moveu DO tableau e a pilha de origem não ficou vazia,
                    // verifica se a nova carta do topo precisa ser virada.
                    if (toupper(origem_str[0]) == 'T' && !pilha_carta_vazia(p_origem)) {
                        Carta nova_topo_origem;
                        // Consulta a nova carta do topo da origem
                        if (pilha_carta_topo(p_origem, &nova_topo_origem)) {
                            if (!nova_topo_origem.virada_para_cima) {
                                printf("Virando a próxima carta em %s...\n", origem_str);
                                // Para virar: desempilha, modifica, empilha de volta
                                if (pilha_carta_desempilhar(p_origem, &nova_topo_origem)) {
                                    nova_topo_origem.virada_para_cima = true;
                                    if (!pilha_carta_empilhar(p_origem, nova_topo_origem)) {
                                        fprintf(stderr, "Erro crítico ao re-empilhar carta virada em %s!\n", origem_str);
                                    }
                                } else {
                                     fprintf(stderr, "Erro ao desempilhar para virar carta em %s!\n", origem_str);
                                }
                            }
                        } else {
                             fprintf(stderr, "Erro ao consultar topo de %s após mover carta.\n", origem_str);
                        }
                    }

                } else {
                    printf("Movimento inválido! Verifique as regras do Paciência.\n");
                }

                break;
            case 's':
            case 'S':
                printf("Saindo do jogo...\n");
                jogo_terminado = true;
                break;
            default:
                printf("Comando desconhecido: '%c'\n", comando);
                break;
        }

        // 4. Verifica condição de vitória (placeholder)
        // if (todas_fundacoes_completas) {
        //     printf("Parabéns, você venceu!\n");
        //     jogo_terminado = true;
        // }
        if (verificar_vitoria(fundacao)) {
            printf("\n****************************************\n");
            printf("*** PARABÉNS! VOCÊ VENCEU O JOGO! ***\n");
            printf("****************************************\n");
            jogo_terminado = true;
        }
    }

    // --- Limpeza Final --- 
    // Destrói todas as pilhas criadas para o jogo
    pilha_carta_destruir(&estoque);
    pilha_carta_destruir(&descarte);
    for (int i = 0; i < 4; ++i) {
        pilha_carta_destruir(&fundacao[i]);
    }
    for (int i = 0; i < 7; ++i) {
        pilha_carta_destruir(&tableau[i]);
    }

    return 0; // Indica que o programa (setup) terminou com sucesso
}


// --- Funções Auxiliares para Movimentação ---

/**
 * @brief Analisa a string de origem e retorna o ponteiro para a pilha correspondente.
 *
 * @param origem_str A string de entrada (ex: "D", "T1", "F3").
 * @param descarte Ponteiro para a pilha de descarte.
 * @param tableau Array de ponteiros para as pilhas do tableau.
 * @param fundacao Array de ponteiros para as pilhas de fundação.
 * @param indice_pilha Ponteiro para armazenar o índice da pilha (para tableau/fundacao).
 * @return PilhaCarta* Ponteiro para a pilha de origem ou NULL se inválida.
 */
PilhaCarta* parse_pilha_origem(const char* origem_str, PilhaCarta* descarte, PilhaCarta* tableau[], PilhaCarta* fundacao[], int* indice_pilha) {
    if (!origem_str || !indice_pilha) return NULL;
    *indice_pilha = -1; // Valor padrão

    if (toupper(origem_str[0]) == 'D' && origem_str[1] == '\0') {
        return descarte;
    } else if (toupper(origem_str[0]) == 'T' && origem_str[1] >= '1' && origem_str[1] <= '7' && origem_str[2] == '\0') {
        *indice_pilha = origem_str[1] - '1'; // Converte '1'.. '7' para 0..6
        return tableau[*indice_pilha];
    } else if (toupper(origem_str[0]) == 'F' && origem_str[1] >= '1' && origem_str[1] <= '4' && origem_str[2] == '\0') {
        *indice_pilha = origem_str[1] - '1'; // Converte '1'.. '4' para 0..3
        // Geralmente não se move DA fundação, mas incluído para análise completa
        return fundacao[*indice_pilha];
    }
    return NULL; // Origem inválida
}

/**
 * @brief Analisa a string de destino e retorna o ponteiro para a pilha correspondente.
 *
 * @param destino_str A string de entrada (ex: "T1", "F3").
 * @param tableau Array de ponteiros para as pilhas do tableau.
 * @param fundacao Array de ponteiros para as pilhas de fundação.
 * @param indice_pilha Ponteiro para armazenar o índice da pilha (para tableau/fundacao).
 * @return PilhaCarta* Ponteiro para a pilha de destino ou NULL se inválida.
 */
PilhaCarta* parse_pilha_destino(const char* destino_str, PilhaCarta* tableau[], PilhaCarta* fundacao[], int* indice_pilha) {
     if (!destino_str || !indice_pilha) return NULL;
    *indice_pilha = -1; // Valor padrão

    if (toupper(destino_str[0]) == 'T' && destino_str[1] >= '1' && destino_str[1] <= '7' && destino_str[2] == '\0') {
        *indice_pilha = destino_str[1] - '1'; // Converte '1'.. '7' para 0..6
        return tableau[*indice_pilha];
    } else if (toupper(destino_str[0]) == 'F' && destino_str[1] >= '1' && destino_str[1] <= '4' && destino_str[2] == '\0') {
        *indice_pilha = destino_str[1] - '1'; // Converte '1'.. '4' para 0..3
        return fundacao[*indice_pilha];
    }
    return NULL; // Destino inválido (não pode mover para Descarte ou Estoque)
}

// Função auxiliar para determinar a cor de uma carta (true para vermelho, false para preto)
bool eh_vermelha(Naipe naipe) {
    return naipe == COPAS || naipe == OUROS;
}

/**
 * @brief Verifica se uma carta pode ser movida para uma pilha de fundação.
 *
 * @param carta_movida A carta que se deseja mover.
 * @param pilha_fundacao A pilha de fundação de destino.
 * @return true Se o movimento for válido, false caso contrário.
 */
bool pode_mover_para_fundacao(Carta carta_movida, const PilhaCarta* pilha_fundacao) {
    if (!pilha_fundacao) return false; // Destino inválido

    if (pilha_carta_vazia(pilha_fundacao)) {
        // Só pode mover um Ás (valor 1) para uma fundação vazia
        return carta_movida.valor == 1;
    } else {
        // Se não estiver vazia, obtém a carta do topo
        Carta topo_fundacao;
        if (!pilha_carta_topo(pilha_fundacao, &topo_fundacao)) {
            return false; // Erro ao obter o topo
        }