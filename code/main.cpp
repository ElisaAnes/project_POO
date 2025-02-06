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

    // Criando três navios para cada jogador
    Peca peca1_1, peca1_2, peca1_3;
    Peca peca2_1, peca2_2, peca2_3;

    // Criando tabuleiros com três navios cada
    Tabuleiro tabuleiro1({&peca1_1, &peca1_2, &peca1_3});
    Tabuleiro tabuleiro2({&peca2_1, &peca2_2, &peca2_3});

    QTimer turnoTimer; // Timer para alternar turnos a cada 10 segundos
    bool turnoJogador1 = true;
    bool fasePosicionamento = true; // Adicionado controle da fase inicial


    // Define o turno inicial
    tabuleiro1.setTurnoAtivo(turnoJogador1);
    tabuleiro2.setTurnoAtivo(!turnoJogador1);


    // Alterna turnos a cada 10 segundos
    // Verifica se ambas as peças foram travadas antes de iniciar o jogo
    QObject::connect(&turnoTimer, &QTimer::timeout, [&]() {
        if (fasePosicionamento) {
            if (tabuleiro1.isPecasTravadas() && tabuleiro2.isPecasTravadas()) {
                qDebug() << "Ambos os jogadores travaram seus navios. O jogo começa agora!";
                fasePosicionamento = false;
                turnoTimer.start(10000); // Iniciar os turnos de ataque normais
            } else {
                qDebug() << "Aguardando ambos os jogadores posicionarem os navios...";
                return;
            }
        } else {
            // Alterna turnos normalmente após o posicionamento
            turnoJogador1 = !turnoJogador1;

            tabuleiro1.setTurnoAtivo(turnoJogador1);
            tabuleiro2.setTurnoAtivo(!turnoJogador1);

            // **Desconectar conexões anteriores para evitar duplicação**
            QObject::disconnect(&tabuleiro1, nullptr, &tabuleiro2, nullptr);
            QObject::disconnect(&tabuleiro2, nullptr, &tabuleiro1, nullptr);

            // **Executar lógica do turno**
            if (turnoJogador1) {
                if (acertos2 == 6) { // 6 acertos (3 navios de 2 partes cada)
                    qDebug() << "Fim de jogo! O Jogador 2 venceu!";
                    QApplication::quit();
                } else {
                    qDebug() << "Vez do Jogador 1:";
                }

                /*if ((tabuleiro2.getLinhaBotao() == peca1.getLinha() && tabuleiro2.getColunaBotao() == peca1.getColuna()) ||
                    (tabuleiro2.getLinhaBotao() == peca1.getLinha2() && tabuleiro2.getColunaBotao() == peca1.getColuna2())) {
                    qDebug() << "Acertou o navio!";
                    acertos1++;
                    qDebug() << "Número de acertos: " << acertos1;*/
                if (tabuleiro2.verificarAcerto(peca1_1) || tabuleiro2.verificarAcerto(peca1_2) || tabuleiro2.verificarAcerto(peca1_3)) {
                    qDebug() << "Acertou o navio!";
                    acertos1++;
                /*} else {
                    qDebug() << "Errou o navio!";
                    qDebug() << "Número de acertos: " << acertos1;*/
                } else {
                    qDebug() << "Errou o navio!";
                }

                tabuleiro1.resetarClique();
                QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarBotao);
                QObject::connect(&tabuleiro1, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarProprio);
            } else {
                if (acertos1 == 6) {
                    qDebug() << "Fim de jogo! O Jogador 1 venceu!";
                    QApplication::quit();
                } else {
                    qDebug() << "Vez do Jogador 2:";
                }

                /*if ((tabuleiro1.getLinhaBotao() == peca2.getLinha() && tabuleiro1.getColunaBotao() == peca2.getColuna()) ||
                    (tabuleiro1.getLinhaBotao() == peca2.getLinha2() && tabuleiro1.getColunaBotao() == peca2.getColuna2())) {
                    qDebug() << "Acertou o navio!";
                    acertos2++;
                    qDebug() << "Número de acertos: " << acertos2;*/
                if (tabuleiro1.verificarAcerto(peca2_1) || tabuleiro1.verificarAcerto(peca2_2) || tabuleiro1.verificarAcerto(peca2_3)) {
                    qDebug() << "Acertou o navio!";
                    acertos2++;
                } else {
                    qDebug() << "Errou o navio!";
                    qDebug() << "Número de acertos: " << acertos2;
                }

                tabuleiro2.resetarClique();
                QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro1, &Tabuleiro::marcarBotao);
                QObject::connect(&tabuleiro2, &Tabuleiro::buttonClicked, &tabuleiro2, &Tabuleiro::marcarProprio);
            }
        }
    });

    turnoTimer.start(10000); // 10 segundos

    tabuleiro1.show();
    tabuleiro2.show();

    return app.exec();
}
