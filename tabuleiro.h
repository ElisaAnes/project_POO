#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>
#include <QTimer>
#include "peca.h" // Inclui a classe Peca corretamente

class Tabuleiro : public QWidget {
    Q_OBJECT

public:
    explicit Tabuleiro(QWidget *parent = nullptr);

    void setTurnoAtivo(bool ativo); // Define se esse tabuleiro pode jogar
    void desativarBotoes(); // Bloqueia todos os botões após um clique

signals:
    void buttonClicked(int row, int col); // Sinal emitido quando um botão for clicado

public slots:
    void marcarBotao(int row, int col); // Slot para marcar um botão correspondente
    void marcarProprio(int row, int col);

private:
    QGridLayout *layout;
    QPushButton *botoes[10][10]; // Armazena os botões do tabuleiro
    Peca *peca; // Ponteiro para a peça vinda de peca.h
    bool turnoAtivo; // Indica se esse tabuleiro pode jogar
    bool botaoSelecionado; // Indica se um botão já foi clicado no turno
};

#endif // TABULEIRO_H
