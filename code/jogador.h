// jogador.h
#ifndef JOGADOR_H
#define JOGADOR_H

#include "peca.h"
#include "tabuleiro.h"
#include <vector>
#include <QDebug>

class Jogador {
public:
    explicit Jogador(Tabuleiro *tabuleiro);
    void posicionarNavios();
    bool realizarAtaque(Tabuleiro *tabuleiroOponente, int linha, char coluna);
    bool todosNaviosTravados() const;
    int getAcertos() const { return acertos; }

    // Métodos adicionais
    void adicionarNavio(Peca *navio);
    void imprimirNavios() const;

private:
    Tabuleiro *meuTabuleiro;
    std::vector<Peca *> navios;
    int acertos;
};

#endif // JOGADOR_H
