#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "peca.h"
#include "tabuleiro.h"

// HUGO sdfdsf


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int acertos1 = 0;
    int acertos2 = 0;

    Peca peca1;
    Peca peca2;  // Criando uma peça separada para cada tabuleiro

    Tabuleiro tabuleiro1(&peca1);
    Tabuleiro tabuleiro2(&peca2);

    QTimer turnoTimer; // Timer para alternar turnos a cada 10 segundos
    bool turnoJogador1 = true;

    // Define o turno inicial
    tabuleiro1.setTurnoAtivo(turnoJogador1);
    tabuleiro2.setTurnoAtivo(!turnoJogador1);


    // Alterna turnos a cada 10 segundos
    QObject::connect(&turnoTimer, &QTimer::timeout, [&]() {
        turnoJogador1 = !turnoJogador1;

        tabuleiro1.setTurnoAtivo(turnoJogador1);
        tabuleiro2.setTurnoAtivo(!turnoJogador1);

        // **1. Desconectar conexões anteriores para evitar duplicação**
        QObject::disconnect(&tabuleiro1, nullptr, &tabuleiro2, nullptr);
        QObject::disconnect(&tabuleiro2, nullptr, &tabuleiro1, nullptr);


        // **2. Conectar apenas os eventos do jogador ativo**
        if (turnoJogador1) {
            if((tabuleiro2.getLinhaBotao() == peca1.getLinha() && tabuleiro2.getColunaBotao() == peca1.getColuna()) || (tabuleiro2.getLinhaBotao() == peca1.getLinha2() && tabuleiro2.getColunaBotao() == peca1.getColuna2())){
                qDebug() << "Acertou o navio!";
                acertos1 ++;
                qDebug() << "Número de acertos:" << acertos1;
            }else{
                qDebug() << "Errou o navio!";
                qDebug() << "Número de acertos:" << acertos1;
            };

            qDebug() << "Vez do Jogador 1:";
            tabuleiro1.resetarClique();
            QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarBotao);
            QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarProprio);

            //qDebug() << "Peça main: (" << peca2.getColuna() << "," << peca2.getLinha() << ") e (" << peca2.getColuna2() << "," << peca2.getLinha2() << ")";

            //qDebug() << "Botão main: (" << tabuleiro2.getColunaBotao() << "," << tabuleiro2.getLinhaBotao() << ")";

        } else {
            if((tabuleiro1.getLinhaBotao() == peca2.getLinha() && tabuleiro1.getColunaBotao() == peca2.getColuna()) || (tabuleiro1.getLinhaBotao() == peca2.getLinha2() && tabuleiro1.getColunaBotao() == peca2.getColuna2())){
                qDebug() << "Acertou o navio!";
                acertos2 ++;
                qDebug() << "Número de acertos:" << acertos2;
            }else{
                qDebug() << "Errou o navio!";

                qDebug() << "Número de acertos:" << acertos2;
            };

            qDebug() << "Vez do Jogador 2:";
            tabuleiro2.resetarClique();
            QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarBotao);
            QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarProprio);

        }
    });

    turnoTimer.start(10000); // 10 segundos

    tabuleiro1.show();
    tabuleiro2.show();

    return app.exec();
}
