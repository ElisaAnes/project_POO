# Análise orientada a objeto
> [!NOTE]
> <p>A <strong>análise</strong> orientada a objeto consiste na descrição do problema a ser tratado, duas primeiras etapas da tabela abaixo, a definição de casos de uso e a definição do domínio do problema.</p>


## Descrição Geral do domínio do problema

O domínio do problema envolve a criação de um jogo de Batalha Naval digital, onde dois jogadores competem para afundar os navios um do outro, posicionados em tabuleiros ocultos. O jogo segue as seguintes regras:

Cada jogador possui um tabuleiro de dimensões fixas (geralmente 10x10).

Os jogadores alternam turnos para atirar em coordenadas no tabuleiro do oponente.

O objetivo é afundar todos os navios do adversário antes que os seus sejam afundados.

O sistema será responsável por:
1) Gerenciar os tabuleiros de cada jogador.
2) Posicionar os navios.
3) Registrar e avaliar os ataques.
4) Determinar o vencedor ao final do jogo.

### Requisitos Funcionais
1) Permitir que cada jogador posicione seus navios no tabuleiro.
2) Registrar as coordenadas dos ataques realizados por cada jogador.
3) Informar se um ataque foi um acerto, erro ou afundou um navio.
4) Indicar o estado atual do jogo, como navios restantes e posição de ataques já realizados.
5) Determinar e declarar o vencedor ao final do jogo.

### Requisitos Não-Funcionais
1) O sistema deve ser intuitivo e fácil de usar, com interface textual ou gráfica simples.
2) O processamento dos turnos deve ser rápido, garantindo fluidez no jogo.
3) O código deve ser modular e organizado, respeitando os princípios de POO.
4) Deve ser possível adicionar novos tipos de navios ou mudar as dimensões do tabuleiro com modificações mínimas.

## Diagrama de Casos de Uso

Aqui estão os principais casos de uso e os atores envolvidos:

### Atores:
1) Jogador: Interage com o sistema para posicionar navios e realizar ataques.
2) Sistema: Gerencia a lógica do jogo.

### Casos de Uso:
1) Posicionar Navio: O jogador define as posições dos navios no tabuleiro.
2) Realizar Ataque: O jogador escolhe uma coordenada para atacar o tabuleiro do oponente.
3) Avaliar Ataque: O sistema verifica se o tiro foi um acerto, erro ou afundou um navio.
4) Exibir Estado Atual do Jogo: O sistema mostra os navios restantes e os ataques já realizados.
5) Declarar Vencedor: O sistema determina e declara o vencedor quando todos os navios de um jogador forem afundados.

 
## Diagrama de Domínio do problema

O diagrama de domínio conceitual identifica os principais elementos e suas relações. Aqui está uma descrição textual para você implementar graficamente:

### Entidades Principais:
1) Tabuleiro: Representa a grade de jogo de cada jogador.
2) Navio: Representa os navios posicionados nos tabuleiros.
3) Jogador: Controla um tabuleiro e realiza ataques.
4) Tiro: Representa um ataque a uma coordenada do tabuleiro.
5) Jogo: Gerencia a interação entre os jogadores.
### Relações:
1) Um Jogador possui um Tabuleiro e pode realizar múltiplos Ataques.
2) Um Tabuleiro contém múltiplos Navios e registra o histórico de Ataques.
3) Um Navio ocupa várias posições no Tabuleiro.
4) O Jogo organiza a sequência de turnos entre os dois Jogadores.

<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
