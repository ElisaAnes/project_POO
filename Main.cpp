#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "peca.h"

class Tabuleiro : public QWidget {
public:
    Tabuleiro(QWidget *parent = nullptr) : QWidget(parent) {
        // Cria o layout em grade para organizar os widgets
        QGridLayout *layout = new QGridLayout(this);

        // Define o espaçamento entre os widgets
        layout->setSpacing(5); // Espaçamento entre os botões

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

        // Adiciona os botões ao tabuleiro (10x10)
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                QPushButton *botao = new QPushButton(this);
                botao->setFixedSize(20, 20);
                botao->setStyleSheet("border-radius: 10px; border: 1px solid black; background-color: lightgray;");
                layout->addWidget(botao, i + 1, j + 1);
                layout->setSpacing(40); // Define o espaçamento entre os widgets (10 pixels, por exemplo)
            }
        }

        // Cria uma peça para o tabuleiro
        Peca *peca = new Peca(this); // Usa a classe personalizada Peca
        layout->addWidget(peca, 6, 6, 2, 2); // Inicialmente posiciona a peça no tabuleiro
        peca->lower(); // Garante que a peça fique acima dos botões

        setLayout(layout);
        setWindowTitle("Tabuleiro com Peça Movível");
        resize(600, 600);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Tabuleiro tabuleiro;
    tabuleiro.show();

    return app.exec();
}
