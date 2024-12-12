# Projeto orientado a objeto

<img src="imagens/class_diagram_3.jpg"
     width="100%"
     style="padding: 10px">

## Classe Servidor
Responsabilidade: Gerenciar as conexões entre os dois jogadores e distribuir as jogadas entre eles.
### Atributos:
server: Um objeto de tipo QTcpServer que aguarda as conexões dos jogadores.
jogador1 e jogador2: São objetos de tipo QTcpSocket que representam os jogadores conectados ao servidor.
### Métodos:
novaConexao(): Estabelece as conexões dos jogadores.
lerDados(): Lê os dados de entrada e processa a jogada.
processarJogada(): Processa a jogada recebida e a envia ao outro jogador.

## Classe Cliente
Responsabilidade: Conectar-se ao servidor e enviar/receber dados sobre as jogadas.
### Atributos:
socket: Objeto QTcpSocket que conecta o cliente ao servidor.
### Métodos:
conectar(): Conecta o cliente ao servidor.
lerDados(): Recebe e processa dados do servidor.
dispararJogada(): Envia as jogadas ao servidor.

## Classe Jogo
Responsabilidade: Controlar o fluxo geral do jogo.
### Atributos:
turno: informações sobre o número de turnos, e jogador da vez.
### Métodos:
iniciar(): Inicia o jogo, configurando jogadores e tabuleiros.
verificarVencedor(): Verifica se há um vencedor (chamando métodos dos jogadores ou tabuleiros para verificar o estado dos navios).

## Classe Jogador
Responsabilidade: Representar um jogador no jogo, contendo as ações específicas de um jogador.
### Atributos:
nome: string: Nome do jogador.
tabuleiro: Tabuleiro: associar o tabuleiro de cada jogador.
### Métodos:
posicionarNavio(): Permite ao jogador posicionar seus navios no tabuleiro.
realizarAtaque(): Realiza um ataque em uma posição do tabuleiro adversário.

## Classe Tabuleiro
Responsabilidade: Representa o tabuleiro de um jogador, armazenando os navios e os tiros disparados.
### Atributos:
navios: QVector: Vetor que armazena os navios posicionados no tabuleiro.
tiros: QVector: Vetor que armazena os tiros disparados no tabuleiro.
### Métodos:
navioAfundado(): Verifica se um navio específico foi afundado.
todosNaviosAfundados(): Verifica se todos os navios no tabuleiro estão afundados.
navioAtingido(): Verifica se um tiro acertou um navio.
foiAtacado(): verifica se um local do tabuleiro já foi atacado.

## Classe Navio:
Responsabilidade: Representar os navios no tabuleiro, controlando seu estado (atingido ou não).
### Atributos:
tamanho: Número de células ocupadas pelo navio.
posicao: QVector: Vetor que armazena as coordenadas ocupadas pelo navio.
acertos: int: Número de vezes que o navio foi atingido.
### Métodos:
foiAtingido(): Marca o navio como atingido em uma posição.
estaAfundado(): Verifica se o navio está afundado (quando o número de acertos for igual ao tamanho).


## Observações:
- A classe Servidor tem uma relação de dependência com a classe Cliente através do uso de QTcpSocket para enviar e receber dados entre os jogadores.
- A classe Tabuleiro contém uma lista de objetos Navio, que representam os navios no tabuleiro.
- A classe Navio contém uma lista de objetos Posicao, que definem as coordenadas ocupadas pelo navio no tabuleiro.
- A classe Posicao é usada para definir as coordenadas de cada célula no tabuleiro.

<div align="center">

[Retroceder](analise.md) | [Avançar](implementacao.md)

</div>
