#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha_cheque.h" // Inclui o cabeçalho específico para a pilha de cheques

// Função auxiliar para ler os dados de um cheque da entrada padrão (teclado)
// Retorna true se a leitura for bem-sucedida, false caso contrário.
bool ler_cheque(int* numero, double* valor) {
    // Tenta ler um inteiro (%d) e um double (%lf) da entrada.
    // scanf retorna o número de itens lidos com sucesso.
    if (scanf("%d %lf", numero, valor) == 2) {
        return true; // Retorna verdadeiro se ambos foram lidos corretamente.
    } else {
        // Se a leitura falhar (ex: usuário digitou texto), limpa o buffer de entrada
        // para evitar que a entrada inválida afete leituras futuras.
        int c; // Variável para armazenar cada caractere lido do buffer
        // Lê e descarta caracteres até encontrar uma nova linha ('\n') ou o fim do arquivo (EOF)
        while ((c = getchar()) != '\n' && c != EOF);
        return false; // Retorna falso indicando que a leitura falhou.
    }
}

int main() { // Função principal do programa
    int capacidade_inicial = 50; // Define a capacidade inicial das pilhas (pode ser ajustada se necessário)
    // Cria a pilha para armazenar os cheques emitidos, usando a função específica do TAD PilhaCheque
    PilhaCheque* pilha_emitidos = pilha_cheque_criar(capacidade_inicial);
    // Cria a pilha para armazenar os cheques pagos
    PilhaCheque* pilha_pagos = pilha_cheque_criar(capacidade_inicial);

    // Verifica se a criação das pilhas falhou (retornou NULL)
    if (!pilha_emitidos || !pilha_pagos) {
        // Imprime uma mensagem de erro se alguma pilha não pôde ser criada
        fprintf(stderr, "Erro ao criar pilhas.\n");
        // Libera a memória da pilha que eventualmente tenha sido criada antes da falha
        if (pilha_emitidos) pilha_cheque_destruir(&pilha_emitidos);
        if (pilha_pagos) pilha_cheque_destruir(&pilha_pagos);
        return 1; // Termina o programa com código de erro
    }

    // Solicita ao usuário para digitar os cheques emitidos
    printf("Digite os cheques emitidos (numero valor), um por linha. Digite 'fim' para parar:\n");
    // Declara uma variável do tipo Cheque (TipoElementoPilha) para armazenar os dados lidos
    TipoElementoPilha cheque_emitido;
    // Loop para ler os cheques emitidos até que ler_cheque retorne false (erro ou 'fim')
    while (ler_cheque(&cheque_emitido.numero, &cheque_emitido.valor)) {
        // Tenta empilhar o cheque lido na pilha de emitidos
        if (!pilha_cheque_empilhar(pilha_emitidos, cheque_emitido)) {
            // Se o empilhamento falhar (pilha cheia), imprime um erro
            // OBS: Uma versão mais robusta poderia redimensionar a pilha aqui.
            fprintf(stderr, "Erro: Pilha de emitidos cheia!\n");
            // O programa continua, mas este cheque não foi adicionado.
        }
    }
    // Após o loop de leitura dos emitidos, limpa o buffer de entrada novamente
    // para garantir que qualquer entrada inválida que parou o loop (como 'fim') seja descartada.
    clearerr(stdin); // Limpa o estado de erro de stdin (necessário após falha de scanf)
    int c; // Variável temporária para caracteres
    // Descarta caracteres até a próxima nova linha ou fim de arquivo
    while ((c = getchar()) != '\n' && c != EOF);


    // Solicita ao usuário para digitar os cheques pagos, informando a ordem esperada
    printf("\nDigite os cheques pagos (numero valor), na ORDEM INVERSA de emissão. Digite 'fim' para parar:\n");
    // Declara uma variável para armazenar os dados do cheque pago lido
    TipoElementoPilha cheque_pago;
    // Loop para ler os cheques pagos
    while (ler_cheque(&cheque_pago.numero, &cheque_pago.valor)) {
        // Tenta empilhar o cheque lido na pilha de pagos
        if (!pilha_cheque_empilhar(pilha_pagos, cheque_pago)) {
            // Se falhar (pilha cheia), imprime um erro
            fprintf(stderr, "Erro: Pilha de pagos cheia!\n");
        }
    }
    // Limpa o buffer de entrada após a leitura dos cheques pagos
    clearerr(stdin);
    // Descarta o restante da linha de entrada
    while ((c = getchar()) != '\n' && c != EOF);

    // --- Início do Processo de Reconciliação ---
    // Imprime o cabeçalho do relatório
    printf("\n--- Relatório de Reconciliação ---\n");
    // %-15s: string alinhada à esquerda em um campo de 15 caracteres
    printf("%-15s %-15s %-15s\n", "NUMERO CHEQUE", "VALOR EMITIDO", "VALOR PAGO");
    // Imprime uma linha separadora
    printf("--------------------------------------------------\n");

    // Variáveis para acumular os totais
    double total_descontado = 0.0;     // Soma dos valores dos cheques pagos e encontrados
    double total_nao_descontado = 0.0; // Soma dos valores dos cheques emitidos e não pagos

    // A pilha 'pilha_emitidos' contém os cheques na ordem inversa de digitação (LIFO).
    // Para comparar com os pagos (que foram digitados na ordem inversa da emissão),
    // precisamos processar os emitidos na ordem original de emissão.
    // Criamos uma pilha temporária para inverter a ordem dos emitidos.
    PilhaCheque* pilha_emitidos_ordem = pilha_cheque_criar(pilha_cheque_tamanho(pilha_emitidos));
    // Move todos os cheques da pilha_emitidos para pilha_emitidos_ordem
    while(!pilha_cheque_vazia(pilha_emitidos)){
        TipoElementoPilha temp; // Variável temporária para o cheque
        // Desempilha da original
        pilha_cheque_desempilhar(pilha_emitidos, &temp);
        // Empilha na temporária (invertendo a ordem)
        pilha_cheque_empilhar(pilha_emitidos_ordem, temp);
    }

    // Agora processa a pilha 'pilha_emitidos_ordem', que está na ordem correta de emissão
    while (!pilha_cheque_vazia(pilha_emitidos_ordem)) {
        TipoElementoPilha emitido; // Variável para o cheque emitido atual
        // Pega o próximo cheque emitido (do mais antigo para o mais novo)
        pilha_cheque_desempilhar(pilha_emitidos_ordem, &emitido);

        TipoElementoPilha pago; // Variável para o cheque pago correspondente (se encontrado)
        bool encontrado_pago = false; // Flag para indicar se o cheque emitido foi pago

        // Verifica se ainda existem cheques na pilha de pagos
        // A pilha 'pilha_pagos' foi preenchida na ordem inversa da emissão, então o topo
        // deve corresponder ao cheque emitido mais antigo que ainda não foi processado.
        if (!pilha_cheque_vazia(pilha_pagos)) {
             // Consulta o cheque no topo da pilha de pagos sem removê-lo
             pilha_cheque_topo(pilha_pagos, &pago);
             // Compara o número do cheque emitido com o número do cheque no topo dos pagos
             if (pago.numero == emitido.numero) {
                // Se os números baterem, o cheque foi pago.
                // Remove (desempilha) o cheque da pilha de pagos
                pilha_cheque_desempilhar(pilha_pagos, &pago);
                // Marca que o cheque foi encontrado
                encontrado_pago = true;
             } else { // Se encontrado_pago for false
                 // Se o número no topo da pilha de pagos não corresponde ao emitido atual,
                 // significa que este cheque emitido não foi pago (assumindo que a entrada
                 // de pagos foi feita corretamente na ordem inversa da emissão).
                 encontrado_pago = false;
             }
        }

        // Verifica se o cheque emitido foi encontrado na pilha de pagos
        if (encontrado_pago) {
            // Adiciona o valor do cheque pago ao total descontado
            total_descontado += pago.valor;
            // Verifica se há diferença entre o valor emitido e o valor pago
            if (emitido.valor != pago.valor) {
                // Imprime a linha no relatório indicando a diferença
                // %-15d: inteiro alinhado à esquerda, 15 espaços
                // %-15.2f: float/double alinhado à esquerda, 15 espaços, 2 casas decimais
                printf("%-15d %-15.2f %-15.2f (Diferença!)\n", emitido.numero, emitido.valor, pago.valor);
            } else { // Se encontrado_pago for false
                 // Se os valores forem iguais, o cheque está OK.
                 // Poderia imprimir uma linha indicando "(OK)
            }
        } else { // Se encontrado_pago for false
            // O cheque emitido não foi encontrado na pilha de pagos.
            // Imprime a linha no relatório indicando que não foi descontado.
            printf("%-15d %-15.2f %-15s (Não descontado)\n", emitido.numero, emitido.valor, "-");
            // Adiciona o valor do cheque emitido ao total não descontado.
            total_nao_descontado += emitido.valor;
        }
    }

    // Após processar todos os emitidos, verifica se sobrou algum cheque na pilha de pagos.
    // Idealmente, esta pilha deveria estar vazia se todos os pagos corresponderam a um emitido.
    while (!pilha_cheque_vazia(pilha_pagos)) {
        TipoElementoPilha pago_extra; // Variável para o cheque pago extra
        // Remove o cheque extra da pilha
        pilha_cheque_desempilhar(pilha_pagos, &pago_extra);
        // Imprime um aviso no erro padrão indicando um cheque pago sem correspondente emitido
        fprintf(stderr, "Aviso: Cheque pago %d (%.2f) não corresponde a nenhum cheque emitido conhecido.\n", pago_extra.numero, pago_extra.valor);
        // O que fazer com este valor? Depende da regra de negócio.
        // Poderia ser adicionado ao total descontado, ignorado, ou tratado como erro.
        // O código atual apenas avisa.
        // total_descontado += pago_extra.valor;
    }

    // Imprime a linha final do relatório
    printf("--------------------------------------------------\n");
    // Imprime os totais calculados, formatados como moeda (R$) com 2 casas decimais.
    printf("TOTAL DESCONTADO     = R$ %.2f\n", total_descontado);
    printf("TOTAL NÃO DESCONTADO = R$ %.2f\n", total_nao_descontado);

    // --- Limpeza Final ---
    // Libera a memória alocada para todas as pilhas criadas
    pilha_cheque_destruir(&pilha_emitidos);       // Destrói a pilha original de emitidos (agora vazia)
    pilha_cheque_destruir(&pilha_pagos);          // Destrói a pilha de pagos (deve estar vazia, exceto por erros)
    pilha_cheque_destruir(&pilha_emitidos_ordem); // Destrói a pilha temporária usada para ordenar

    return 0; // Indica que o programa terminou com sucesso
}