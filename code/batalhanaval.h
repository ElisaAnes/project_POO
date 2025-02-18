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

    Tabuleiro *tabuleiro1;
    Tabuleiro *tabuleiro2;

    int acertos1;
    int acertos2;

    bool turnoJogador1;
    bool fasePosicionamento;

    QTimer turnoTimer;

    void marcarAtaqueNoTabuleiro(Tabuleiro *tabuleiro, int linha, char coluna, const QString &caminhoImagem);
    void configurarJogo();
    void alternarTurno();
    bool verificarAcerto(Tabuleiro *tabuleiro, Peca *pecas[], int tamanho);
    void mostrarImagem(Tabuleiro *tabuleiro, const QString &caminhoImagem, int x, int y, int largura, int altura);
};

#endif // BATALHANAVAL_H
