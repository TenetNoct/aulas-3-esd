#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // Inclui a biblioteca matemática para funções como pow() (potência), isnan()
#include "pilha_double.h" // Inclui o cabeçalho específico para a pilha de doubles

// Função auxiliar para verificar se um caractere é um dos operadores suportados (+, -, *, /)
// Retorna true se for um operador válido, false caso contrário.
bool eh_operador(char c) {
    // Compara o caractere 'c' com cada um dos operadores válidos
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função auxiliar para realizar a operação aritmética entre dois operandos
// Recebe os dois operandos (op1, op2) e o caractere do operador.
// Retorna o resultado da operação ou NaN (Not a Number) em caso de erro (divisão por zero).
double calcular(double op1, double op2, char operador) {
    // Usa uma estrutura switch para determinar qual operação realizar com base no operador
    switch (operador) {
        case '+': return op1 + op2; // Soma
        case '-': return op1 - op2; // Subtração
        case '*': return op1 * op2; // Multiplicação
        case '/': // Divisão
            // Verifica se o segundo operando (divisor) é zero
            if (op2 == 0) {
                // Imprime uma mensagem de erro se for divisão por zero
                fprintf(stderr, "Erro: Divisão por zero!\n");
                // Retorna NaN (Not a Number) para indicar o erro de divisão por zero.
                // NAN é definido em <math.h>.
                #ifdef NAN // Verifica se a macro NAN está definida (padrão C99)
                    return NAN; // Retorna o valor NaN
                #else // Se NAN não estiver definido (compiladores mais antigos)
                    // Gera NaN manualmente dividindo 0.0 por 0.0 (comportamento padrão IEEE 754)
                    return 0.0 / 0.0;
                #endif
            }
            // Se o divisor não for zero, realiza a divisão
            return op1 / op2;
        // Outros operadores poderiam ser adicionados aqui, como potência:
        // case '^': return pow(op1, op2); // Calcula op1 elevado a op2
        default: // Caso o caractere não seja nenhum dos operadores esperados
            // Imprime uma mensagem de erro indicando operador inválido
            fprintf(stderr, "Erro: Operador desconhecido '%c'\n", operador);
            // Retorna NaN para indicar erro
            #ifdef NAN
                return NAN;
            #else
                return 0.0 / 0.0;
            #endif
    }
}

int main() { // Função principal do programa
    char expressao[256]; // Declara um array de caracteres (string) para armazenar a expressão pré-fixada lida
    PilhaDouble* pilha_operandos = NULL; // Declara um ponteiro para a pilha de operandos (doubles), inicializado como NULL

    // Solicita ao usuário que digite a expressão pré-fixada
    printf("Digite a expressão pré-fixada (operandos e operadores separados por espaço):\n");
    // Lê a linha inteira digitada pelo usuário (incluindo espaços) para dentro do buffer 'expressao'
    // fgets é mais seguro que scanf para ler strings, pois evita buffer overflow.
    // sizeof(expressao) garante que não lerá mais caracteres do que o buffer pode conter.
    // stdin indica que a leitura é da entrada padrão (teclado).
    // Verifica se a leitura falhou (fgets retorna NULL em caso de erro ou fim de arquivo)
    if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
        // Imprime mensagem de erro se a leitura falhar
        fprintf(stderr, "Erro ao ler a expressão.\n");
        return 1; // Termina o programa com código de erro
    }

    // fgets geralmente inclui o caractere de nova linha ('\n') no final da string, se houver espaço.
    // strcspn(expressao, "\n") encontra o índice do primeiro '\n' na string.
    // Substitui esse '\n' por um caractere nulo ('\0' ou 0) para terminar a string corretamente.
    expressao[strcspn(expressao, "\n")] = 0;

    // --- Início da Avaliação da Expressão Pré-fixada ---
    // A avaliação pré-fixada requer processar a expressão da DIREITA para a ESQUERDA.

    // Cria a pilha de operandos usando a função específica do TAD PilhaDouble
    pilha_operandos = pilha_double_criar(50); // Define uma capacidade inicial (ex: 50)
    // Verifica se a criação da pilha falhou
    if (!pilha_operandos) {
        // Imprime erro se a pilha não pôde ser criada
        fprintf(stderr, "Erro ao criar a pilha de operandos.\n");
        return 1;
    }

    // Divide a string 'expressao' em 'tokens' (palavras) usando o espaço como delimitador.
    // Como precisamos processar da direita para a esquerda, primeiro armazenamos todos os tokens.
    char* tokens[128]; // Cria um array de ponteiros de caracteres para armazenar os endereços dos tokens.
    int num_tokens = 0; // Contador para o número de tokens encontrados.
    // strtok modifica a string original, inserindo '\0' nos delimitadores.
    // A primeira chamada a strtok recebe a string a ser tokenizada.
    char* token = strtok(expressao, " "); // Pega o primeiro token
    // Loop para encontrar todos os tokens na string
    // Continua enquanto strtok encontrar tokens (não retornar NULL) e não exceder a capacidade do array 'tokens'.
    while (token != NULL && num_tokens < 128) {
        // Armazena o ponteiro para o token atual no array 'tokens'
        tokens[num_tokens++] = token;
        // As chamadas subsequentes a strtok devem passar NULL como primeiro argumento
        // para continuar tokenizando a mesma string de onde parou.
        token = strtok(NULL, " "); // Pega o próximo token
    }

    // Agora, itera sobre os tokens armazenados, começando do último (direita) até o primeiro (esquerda)
    for (int i = num_tokens - 1; i >= 0; i--) {
        // Pega o token atual do array
        token = tokens[i];

        // Tenta converter o token atual para um número double usando strtod.
        char* endptr; // Ponteiro para armazenar o caractere onde a conversão parou.
        // strtod converte a parte inicial da string 'token' para double.
        double operando = strtod(token, &endptr);

        // Verifica se a conversão foi bem-sucedida:
        // 1. endptr != token: Garante que pelo menos um caractere foi convertido.
        // 2. *endptr == '\0': Garante que a conversão consumiu toda a string do token (não parou no meio).
        if (endptr != token && *endptr == '\0') { // Se for um número válido...
            // Empilha o operando (número) na pilha de operandos.
            if (!pilha_double_empilhar(pilha_operandos, operando)) {
                // Imprime erro se a pilha estiver cheia.
                fprintf(stderr, "Erro: Pilha de operandos cheia ao empilhar %f!\n", operando);
                // Libera a memória da pilha antes de sair.
                pilha_double_destruir(&pilha_operandos);
                return 1;
            }
        // Se não for um número, verifica se é um operador válido.
        // Condições: O token tem exatamente 1 caractere E esse caractere é um operador reconhecido pela função eh_operador.
        } else if (strlen(token) == 1 && eh_operador(token[0])) { // Se for um operador...
            char operador = token[0]; // Armazena o caractere do operador.
            double op1, op2; // Variáveis para armazenar os dois operandos desempilhados.

            // Desempilha o primeiro operando (que foi empilhado por último).
            if (!pilha_double_desempilhar(pilha_operandos, &op1)) {
                // Erro: Pilha vazia, não há operandos suficientes para o operador.
                fprintf(stderr, "Erro: Faltam operandos para o operador '%c'.\n", operador);
                pilha_double_destruir(&pilha_operandos);
                return 1;
            }
            // Desempilha o segundo operando.
            if (!pilha_double_desempilhar(pilha_operandos, &op2)) {
                // Erro: Pilha continha apenas um operando.
                fprintf(stderr, "Erro: Falta o segundo operando para o operador '%c'.\n", operador);
                 // Opcional: Poderia empilhar op1 de volta se quisesse tentar continuar,
                 // mas geralmente um erro de expressão invalida o cálculo.
                 // pilha_double_empilhar(pilha_operandos, op1);
                pilha_double_destruir(&pilha_operandos);
                return 1;
            }

            // Chama a função 'calcular' para realizar a operação com os dois operandos desempilhados.
            double resultado = calcular(op1, op2, operador);

            // Verifica se o resultado é NaN (Not a Number), o que indica um erro no cálculo (como divisão por zero).
            // isnan() é da biblioteca <math.h>.
            if (isnan(resultado)) {
                 // Imprime uma mensagem de erro se o cálculo resultou em NaN.
                 fprintf(stderr, "Erro durante o cálculo com o operador '%c'.\n", operador);
                 pilha_double_destruir(&pilha_operandos);
                 return 1;
            }

            // Empilha o resultado da operação de volta na pilha.
            if (!pilha_double_empilhar(pilha_operandos, resultado)) {
                // Erro se a pilha estiver cheia ao tentar empilhar o resultado.
                fprintf(stderr, "Erro: Pilha de operandos cheia ao empilhar resultado %f!\n", resultado);
                pilha_double_destruir(&pilha_operandos);
                return 1;
            }
        } else { // Se o token não for nem um número válido nem um operador válido...
            // Imprime uma mensagem de erro indicando um token desconhecido na expressão.
            fprintf(stderr, "Erro: Token inválido na expressão: '%s'\n", token);
            pilha_double_destruir(&pilha_operandos);
            return 1;
        }
    }

    // --- Verificação do Resultado Final ---
    double resultado_final; // Variável para armazenar o resultado final da expressão.
    // Após processar todos os tokens, a pilha deve conter exatamente um elemento: o resultado final.
    // Verifica se o tamanho da pilha é 1 E se conseguimos desempilhar esse único elemento.
    if (pilha_double_tamanho(pilha_operandos) == 1 && pilha_double_desempilhar(pilha_operandos, &resultado_final)) {
        // Se a condição for verdadeira, imprime o resultado final formatado com 2 casas decimais.
        printf("\nResultado da expressão: %.2f\n", resultado_final);
    // Se a pilha estiver vazia no final, a expressão era inválida ou vazia.
    } else if (pilha_double_vazia(pilha_operandos)){
         // Imprime mensagem de erro.
         fprintf(stderr, "\nErro: Expressão inválida ou vazia. Nenhum resultado.\n");
         pilha_double_destruir(&pilha_operandos);
         return 1;
    } else { // Se a pilha não estiver vazia e não tiver tamanho 1...
        // Erro: A expressão era inválida, pois sobraram operandos na pilha após o processamento.
        // Imprime quantos operandos extras sobraram.
        fprintf(stderr, "\nErro: Expressão inválida. Sobraram operandos na pilha (%d).\n", pilha_double_tamanho(pilha_operandos));
        // Opcional: Poderia desempilhar e imprimir os operandos restantes para ajudar na depuração.
        // while(pilha_double_desempilhar(pilha_operandos, &resultado_final)) {
        //     fprintf(stderr, " - Operando restante: %f\n", resultado_final);
        // }
        pilha_double_destruir(&pilha_operandos);
        return 1;
    }

    // --- Limpeza Final ---
    // Garante que a pilha seja destruída e a memória liberada, mesmo que já tenha sido destruída em caso de erro.
    // Chamar destruir em um ponteiro NULL é seguro.
    pilha_double_destruir(&pilha_operandos);

    return 0; // Indica que o programa terminou com sucesso (se chegou até aqui sem erros fatais).
}