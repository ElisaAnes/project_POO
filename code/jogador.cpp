// jogador.cpp
#include "jogador.h"

Jogador::Jogador(Tabuleiro *tabuleiro) : meuTabuleiro(tabuleiro), acertos(0) {}

void Jogador::posicionarNavios() {
    QGridLayout* layout = meuTabuleiro->getLayout();

    for (Peca *navio : navios) {
        layout->addWidget(navio, navio->getRow(), navio->getCol());
    }
}

bool Jogador::realizarAtaque(Tabuleiro *tabuleiroOponente, int linha, char coluna) {
    for (Peca *navio : tabuleiroOponente->getNavios()) { // ✅ Agora acessamos os navios corretamente
        if ((navio->getLinha() == linha && navio->getColuna() == coluna) ||
            (navio->getLinha2() == linha && navio->getColuna2() == coluna)) {
            acertos++;
            return true;
        }
    }
    return false;
}

bool Jogador::todosNaviosTravados() const {
    for (Peca *navio : navios) {
        if (!navio->isLocked()) {
            return false;
        }
    }
    return true;
}

void Jogador::adicionarNavio(Peca *navio) {
    navios.push_back(navio);
}

void Jogador::imprimirNavios() const {
    for (const Peca *navio : navios) {
        qDebug() << "Navio em:" << navio->getLinha() << navio->getColuna();
    }
}
