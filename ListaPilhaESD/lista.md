Lista de exercícios: Pilha
01) Um registro contendo o número do cheque e o seu valor é preparado para cada cheque
emitido para os empregados da Vinhos Nariz Vermelho Ltda. No fim de cada mês, todos os
cheques pagos (descontados) são coletados no banco e um registro similar é digitado para
cada cheque, na ordem inversa a que foram emitidos , para formar a entrada do algoritmo de
reconciliação, isto é, casar os cheques emitidos com aqueles recebidos.
Uma entrada típica é ilustrada a seguir, mostrando casos que podem ocorrer:
23871 4850.20 Cheque 23871 emitido e descontado para R$ 4.850.20.
23871 4850.20
23872 15000.00 Cheque 23872 emitido para R$ 15 .000.00 mas não
descontado
23873 3620.40 Cheque 23873 emitido para R$ 3620.40 e descontado para

um valor diferente

23873 23620.40

O algoritmo de reconciliação lista os cheques emitidos, mas ainda não descontados, e
imprime o número do cheque e as duas quantidades para qualquer cheque emitido e
descontado com um valor diferente. Também são impressos o valor total de cheques
descontados e o valor total dos cheques ainda não descontados.

NÚMERO DO CHEQUE VALOR
23872 15000.00
23873 3620.40 23620.40
. .
. .
. .
TOTAL DESCONTADO = R$ 1237614.20
TOTAL NÃO DESCONTADO = R$ 87314.90

02) Uma forma de expressão fácil de ser avaliada e com parênteses livres é chamada de pré-
fixada. Nesta maneira de escrever expressões, os operadores precedem seus operandos.
Por exemplo:

infixa pré-fixada
A * B / C / * ABC
A / B ** C + D * E - A * C - + / A ** BC * DE * AC
A * ( B + C ) / D - G - / * A + BCDG

Faça um programa que avalie uma expressão desse tipo, introduzindo via teclado.
OBS: As variáveis tem seu valor introduzidos também via teclado antes da expressão.
03) Um dos jogos é a paciência, que está descrita abaixo. Sua designação consiste em escrever
um programa de computador para fazer o jogo, assim liberando horas de tempo para pessoas
poderem retornar a objetivos mais úteis.
Para começar o jogo, dá-se 28 cartas distribuídas em 7 pilhas. A pilha mais à esquerda terá 1
carta, a próxima 2 e assim por diante até 7 cartas na pilha mais à direita. Apenas a carta de
topo, em cada uma das 7 pilhas, será virada com a face para cima. As cartas são dadas da

esquerda para a direita, uma carta para cada pilha, distribuindo para uma pilha a menos em
cada retorno, como também virando a primeira carta com face para cima. Você pode formar
agora seqüências decrescentes, naipe preto sobre vermelho e vermelho sobre o preto, usando
as cartas descobertas. Por exemplo, sobre o 9 de espadas, você pode colocar tanto 8 de ouros
como 8 de copas. O grupo de cartas descobertas de uma pilha pode ser movido como unidade
para outra pilha, de acordo com a carta mais no fundo da pilha. Por exemplo, o 7 de paus
sobre 8 de copas pode ser movido como unidade e colocado sobre 9 de paus ou 9 de espadas.
Cada vez que se descobre uma pilha, sua carta deve ser virada com a face para cima. Quando
uma pilha for removida completamente, um Rei pode ser movido para aquele lugar vago
(junto com todas as cartas sobre ele) mesmo se ele vem do topo da pilha de restos (veja
abaixo). O objetivo do jogo é colocar o máximo de cartas nas pilhas de saída, que são quatro,
um para cada naipe. Sempre quando aparece um Ás no topo de uma pilha ou no topo da pilha
de restos, ele deve ser movido para iniciar uma pilha de saída apropriada. Acrescentam-se as
cartas nas pilhas de saída em seqüência crescente, o naipe sendo determinado pelo Ás no
fundo.
Do resto do baralho, chamado estoque, as cartas são viradas uma por uma e colocadas com
face para cima sobre a pilha de resto. Você pode sempre jogar as cartas colocadas na pilha de
resto, porém uma de cada vez. Comece colocando uma carta do estoque no topo da pilha de
resto. Havendo mais do que uma jogada a ser feita, deve ser observada a seguinte ordem:
1) Mova uma carta do topo da pilha de jogo ou da pilha de resto para a pilha de saída. Se a
pilha de resto estiver vazia, coloque nela uma carta do estoque.
2) Mova uma carta do topo da pilha de resto para a pilha de jogo mais à esquerda, para a
qual pode ser movida. Se a pilha de resto estiver vazia, coloque nela uma carta do
estoque.
3) Encontre a pilha de jogo, mais à esquerda, que pode ser movida, e coloque-a por cima da
pilha de jogo, mais à esquerda, para onde ela pode ser movida.
4) Faça as tentativas A), B) e C) na sequência, reiniciando com A) sempre quando for feito um
movimento.
5) Se não há mais movimentos por meio de (A) até (D) retire uma nova carta do estoque e
repita as tentativas começando com (A).
Apenas a carta de topo da pilha de jogo ou da pilha de resto pode ser jogada para a pilha de
saída. Uma vez encontrando-se na pilha de saída, nenhuma carta pode ser retirada para ajudar
em outro lugar. O jogo termina quando ou:

a- Todas as cartas foram jogadas para a saída ou
b- A pilha de estoque esgotou-se e não há mais cartas a serem movidas.
Quando jogado a dinheiro, o jogador começa pagando R$52 para o estabelecimento e ganha
R$ 5 para cada carta jogada para as pilhas de saída.
Escreva os seu programa para ele jogar várias vezes e determine seu lucro líquido. Use um
gerador de números aleatórios para embaralhar.
Inclua a saída de registro completo de dois jogos em uma forma compreensível. Inclua
também na saída a quantidade de jogos feitos e o lucro líquido ( + ou - ).