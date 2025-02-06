#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>
#include "peca.h" // Inclui a classe Peca corretamente

class Tabuleiro : public QWidget {
    Q_OBJECT

public:
    //explicit Tabuleiro(Peca *peca, QWidget *parent = nullptr);
    explicit Tabuleiro(std::vector<Peca *> pecas, QWidget *parent = nullptr);

    void setTurnoAtivo(bool ativo); // Define se esse tabuleiro pode jogar
    void desativarBotoes(); // Bloqueia todos os botões após um clique
    bool isBotaoClicado() const; // Retorna true se um botão foi clicado
    void resetarClique(); // Reseta a variável para permitir um novo clique no próximo turno
    int getLinhaBotao() const; // Retorna a segunda linha se for vertical
    char getColunaBotao() const; // Retorna a coluna principal da peça
    bool isPecaTravada() const; // Adicionada para verificar se a peça foi travada
    bool isPecasTravadas() const; // Verifica se todos os navios estão travados

    bool verificarAcerto(const Peca &peca) const; // Verifica se um tiro acertou um navio


signals:
    void buttonClicked(int row, int col); // Sinal emitido quando um botão for clicado

public slots:
    void marcarBotao(int row, int col); // Slot para marcar um botão correspondente
    void marcarProprio(int row, int col);

private:
    QGridLayout *layout;
    QPushButton *botoes[10][10]; // Armazena os botões do tabuleiro
    //Peca *peca; // Ponteiro para a peça vinda de peca.h
    std::vector<Peca *> pecas;
    bool turnoAtivo; // Indica se esse tabuleiro pode jogar
    bool botaoSelecionado; // Indica se um botão já foi clicado no turno
    bool botaoClicado; // Indica se um botão já foi clicado no turno
    int linha;
    char coluna;
};

#endif // TABULEIRO_H
