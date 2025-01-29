#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>
#include "peca.h" // Inclui a classe Peca corretamente

class Tabuleiro : public QWidget {
    Q_OBJECT

public:
    explicit Tabuleiro(QWidget *parent = nullptr);

signals:
    void buttonClicked(int row, int col); // Sinal emitido quando um botão for clicado

public slots:
    void marcarBotao(int row, int col); // Slot para marcar um botão correspondente
    void marcarProprio(int row, int col);

private:
    QGridLayout *layout;
    QPushButton *botoes[10][10]; // Armazena os botões do tabuleiro
    Peca *peca; // Ponteiro para a peça vinda de peca.h
};

#endif // TABULEIRO_H
