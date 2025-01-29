#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "peca.h"
#include "tabuleiro.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Criamos duas instâncias do tabuleiro corretamente
    Tabuleiro tabuleiro1;
    Tabuleiro tabuleiro2;

    // Conectamos os sinais e slots para sincronizar os cliques
    QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarBotao);
    QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarBotao);


    // Exibir os tabuleiros
    tabuleiro1.show();
    tabuleiro2.show();

    return app.exec();
}
