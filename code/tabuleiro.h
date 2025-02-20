#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "peca.h"

class Tabuleiro : public QWidget {
    Q_OBJECT

public:
    explicit Tabuleiro(std::vector<Peca *> pecas, QWidget *parent = nullptr);

    int getLinhaBotao() const;
    char getColunaBotao() const;
    QPushButton* getBotao(int linha, int coluna);

    void setTurnoAtivo(bool ativo);
    void desativarBotoes();
    bool isBotaoClicado() const;
    void resetarClique();
    bool isPecasTravadas() const;
    bool verificarAcerto(const Peca &peca) const;
    QGridLayout* getLayout() { return layout; }
    std::vector<Peca *> getNavios() const { return pecas; }

signals:
    void buttonClicked(int row, int col);

public slots:
    void marcarBotao(int row, int col);
    void marcarProprio(int row, int col);

private:
    QGridLayout *layout;
    QPushButton *botoes[10][10];
    std::vector<Peca *> pecas;


    bool turnoAtivo;
    bool botaoClicado;  // 🔹 Substituindo 'botaoSelecionado' por 'botaoClicado'
    int linha;
    char coluna;
};

#endif // TABULEIRO_H
