#ifndef BATALHANAVAL_H
#define BATALHANAVAL_H

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "peca.h"
#include "tabuleiro.h"

class BatalhaNaval : public QObject {
    Q_OBJECT

public:
    explicit BatalhaNaval(QObject *parent = nullptr);

private:
    Peca peca1_1, peca1_2, peca1_3;
    Peca peca2_1, peca2_2, peca2_3;

    Tabuleiro *tabuleiro1;  // Agora será uma janela separada
    Tabuleiro *tabuleiro2;  // Agora será uma janela separada

    int acertos1;
    int acertos2;

    bool turnoJogador1;
    bool fasePosicionamento;

    QTimer turnoTimer;

    void configurarJogo();
    void alternarTurno();
};

#endif // BATALHANAVAL_H
