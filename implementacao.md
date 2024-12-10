# Implementação

>[!NOTE] 
 Relatar o processo de implementação do problemas, incluindo as
 ferramentas e bibliotecas utilizadas
>

## Interface Tabuleiro
A classe QPushButton será usada para criar um tabuleiro no jogo de batalha naval. Cada botão reprensentará uma célula do tabuleiro, o comportamento do botão será configurado para reagir às ações do jogador, como clicar para realizar ataque ou exibir estado de uma célula.
### Estrutura do Tabuleiro
Grade de botões: a classe QGridLayout será usada para organizar os botões em uma matriz que representará o tabuleiro.
Identificação das células: cada botão será associado a uma coordenada específica do tabuleiro, através de linha e coluna.

## Definição dos Turnos
Existem dois objetos "Jogador", um ponteiro "Jogador* jogadorAtual" apontará para o jogador que inicia o jogo "&jogador1".
Após a jogada, alterar ponteiro para apontar para "&jogador2"
Exemplo de lógica:

Jogador* jogadorAtual = &jogador1;

if (jogadorAtual == &jogador1) {
            jogadorAtual = &jogador2;
        } else {
            jogadorAtual = &jogador1;
        }


<div align="center">

[Retroceder](projeto.md) | [Início](analise.md)

</div>
