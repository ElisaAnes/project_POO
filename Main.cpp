#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "peca.h"
#include "tabuleiro.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Tabuleiro tabuleiro1;
    Tabuleiro tabuleiro2;

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
            QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarBotao);
            QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarProprio);
        } else {
            QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarBotao);
            QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarProprio);
        }
    });

    turnoTimer.start(10000); // 10 segundos

    tabuleiro1.show();
    tabuleiro2.show();

    return app.exec();
}
