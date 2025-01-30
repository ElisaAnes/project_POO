#include "tabuleiro.h"

Tabuleiro::Tabuleiro(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setSpacing(40); // Define o espaçamento entre os botões

    peca = new Peca(this); // Instancia a peça corretamente a partir de peca.h

    // Adiciona rótulos no topo do tabuleiro (letras de A a J)
    for (int col = 0; col < 10; ++col) {
        QLabel *letra = new QLabel(QString(QChar('A' + col)), this);
        letra->setAlignment(Qt::AlignCenter);
        layout->addWidget(letra, 0, col + 1);
    }

    // Adiciona rótulos na lateral esquerda do tabuleiro (números de 1 a 10)
    for (int row = 0; row < 10; ++row) {
        QLabel *numero = new QLabel(QString::number(row + 1), this);
        numero->setAlignment(Qt::AlignCenter);
        layout->addWidget(numero, row + 1, 0);
    }

    // Criar os botões do tabuleiro (10x10)
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            botoes[i][j] = new QPushButton(this);
            botoes[i][j]->setFixedSize(20, 20);
            botoes[i][j]->setStyleSheet("border-radius: 10px; border: 1px solid black; background-color: lightgray;");
            layout->addWidget(botoes[i][j], i + 1, j + 1);

            // Conectando o botão ao sinal
            connect(botoes[i][j], &QPushButton::clicked, [this, i, j]() {
                emit buttonClicked(i, j);
            });
        }
    }

    // Captura `this` na lambda para acessar os membros da classe corretamente
    connect(peca, &QPushButton::clicked, this, [this]() {
        if (peca->isPieceVertical()) {
            layout->addWidget(peca, peca->getRow(), peca->getCol(), 2, 1);
        } else {
            layout->addWidget(peca, peca->getRow(), peca->getCol(), 1, 2);
        }
    });

    setLayout(layout);
    setWindowTitle("Tabuleiro");
    resize(600, 600);
}

// Define se esse tabuleiro pode jogar e reseta estado
void Tabuleiro::setTurnoAtivo(bool ativo) {
    turnoAtivo = ativo;
    botaoSelecionado = false; // Reseta a variável para novo turno

    if (turnoAtivo) {
        setWindowTitle("Seu Turno");
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                botoes[i][j]->setEnabled(true); // Ativa os botões para o turno
            }
        }
    } else {
        setWindowTitle("Aguardando...");
        desativarBotoes(); // Desativa os botões quando não for o turno
    }
}

// Bloqueia todos os botões do tabuleiro
void Tabuleiro::desativarBotoes() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            botoes[i][j]->setEnabled(false);
        }
    }
}

// Método para marcar o botão correspondente
void Tabuleiro::marcarBotao(int row, int col) {
    QString estiloAtual = botoes[row][col]->styleSheet(); // Obtém o estilo atual
    QString corBorda = "black"; // Valor padrão caso a borda não esteja definida

    // Expressão regular para encontrar a cor da borda no estilo atual
    QRegularExpression regex("border:\\s*[^;]+\\s+solid\\s+([^;]+);");
    QRegularExpressionMatch match = regex.match(estiloAtual);

    if (match.hasMatch()) {
        corBorda = match.captured(1); // Captura a cor da borda atual
    }

    // Define o novo estilo mantendo a borda e alterando apenas o background-color
    QString novoEstilo = QString("background-color: yellow; border-radius: 10px; border: 2px solid %1;").arg(corBorda);
    botoes[row][col]->setStyleSheet(novoEstilo);
}

// Método para marcar o botão correspondente
void Tabuleiro::marcarProprio(int row, int col) {
    QString estiloAtual = botoes[row][col]->styleSheet(); // Pega o estilo atual
    QString corAtual = "lightgray"; // Valor padrão caso não encontre a cor

    // Expressão regular para encontrar a cor de fundo no estilo atual
    QRegularExpression regex("background-color:\\s*([^;]+);");
    QRegularExpressionMatch match = regex.match(estiloAtual);

    if (match.hasMatch()) {
        corAtual = match.captured(1); // Captura a cor de fundo atual
    }

    // Define o novo estilo mantendo a cor e alterando apenas a borda
    QString novoEstilo = QString("background-color: %1; border-radius: 10px; border: 2px solid red;").arg(corAtual);
    botoes[row][col]->setStyleSheet(novoEstilo);
}
