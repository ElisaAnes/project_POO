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

// Método para marcar o botão correspondente
void Tabuleiro::marcarBotao(int row, int col) {
    botoes[row][col]->setStyleSheet("background-color: yellow; border-radius: 10px; border: 2px solid black;");
}
