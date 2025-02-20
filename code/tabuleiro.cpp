#include "tabuleiro.h"
#include <QRegularExpression>


// tabuleiro.cpp
#include "tabuleiro.h"

Tabuleiro::Tabuleiro(std::vector<Peca *> pecas, QWidget *parent) : QWidget(parent), pecas(pecas) {
    layout = new QGridLayout(this);
    layout->setSpacing(40);

    for (Peca *peca : pecas) {
        peca->setParent(this);
        layout->addWidget(peca, peca->getRow(), peca->getCol(), 1, 2);
    }


    // Adiciona rótulos no topo do tabuleiro (A-J)
    for (int col = 0; col < 10; ++col) {
        QLabel *letra = new QLabel(QString(QChar('A' + col)), this);
        letra->setAlignment(Qt::AlignCenter);
        layout->addWidget(letra, 0, col + 1);
    }

    // Adiciona rótulos na lateral esquerda do tabuleiro (1-10)
    for (int row = 0; row < 10; ++row) {
        QLabel *numero = new QLabel(QString::number(row + 1), this);
        numero->setAlignment(Qt::AlignCenter);
        layout->addWidget(numero, row + 1, 0);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            botoes[i][j] = new QPushButton(this); // 🔹 Criando o botão corretamente
            botoes[i][j]->setFixedSize(20, 20);
            botoes[i][j]->setStyleSheet("border-radius: 10px; border: 1px solid black; background-color: lightgray;");
            layout->addWidget(botoes[i][j], i + 1, j + 1);

            // Conectar apenas se o botão existir
            if (botoes[i][j]) {
                connect(botoes[i][j], &QPushButton::clicked, this, [this, i, j]() {
                    if (!botaoClicado) {
                        botaoClicado = true;
                        coluna = 'A' + j;
                        linha = i + 1;
                        qDebug() << "Botão clicado em: (" << coluna << "," << linha << ")";
                        emit buttonClicked(i, j);
                    }
                });
            } else {
                qDebug() << "Erro: Tentando conectar um botão que é nullptr!";
            }
        }
    }


    // Ajuste inicial das peças
    for (Peca *peca : pecas) {
        peca->setPosition(7, 7); // Definir posições iniciais
        connect(peca, &QPushButton::clicked, this, [this, peca]() {
            if (peca->isPieceVertical()) {
                layout->addWidget(peca, peca->getRow(), peca->getCol(), 2, 1);
            } else {
                layout->addWidget(peca, peca->getRow(), peca->getCol(), 1, 2);
            }
        });
    }

    setLayout(layout);
    setWindowTitle("Tabuleiro");
    resize(600, 600);
}

void Tabuleiro::setTurnoAtivo(bool ativo) {
    turnoAtivo = ativo;
    botaoClicado = false; // ✅ Agora usamos 'botaoClicado' corretamente

    if (turnoAtivo) {
        setWindowTitle("Seu Turno");
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                botoes[i][j]->setEnabled(true);
            }
        }
    } else {
        setWindowTitle("Aguardando...");
        desativarBotoes();
    }
}


// Verifica se todos os navios estão travados
bool Tabuleiro::isPecasTravadas() const {
    for (const Peca *peca : pecas) {
        if (!peca->isLocked()) {
            return false;
        }
    }
    return true;
}
/*
// Verifica se um tiro acertou um dos navios
bool Tabuleiro::verificarAcerto(const Peca &peca) const {
    return (linha == peca.getLinha() && coluna == peca.getColuna()) ||
           (linha == peca.getLinha2() && coluna == peca.getColuna2());
}
*/

// Verifica se um tiro acertou um dos navios
bool Tabuleiro::verificarAcerto(const Peca &peca) const {
    return (linha == peca.getLinha() && coluna == peca.getColuna()) ||
           (linha == peca.getLinha2() && coluna == peca.getColuna2());
}

// Bloqueia todos os botões do tabuleiro
void Tabuleiro::desativarBotoes() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            botoes[i][j]->setEnabled(false);
        }
    }
}

// Método para marcar o botão correspondente
void Tabuleiro::marcarBotao(int row, int col) {
    QString estiloAtual = botoes[row][col]->styleSheet(); // Obtém o estilo atual
    QString corBorda = "black"; // Valor padrão caso a borda não esteja definida

    // Expressão regular para encontrar a cor da borda no estilo atual
    QRegularExpression regex("border:\\s*[^;]+\\s+solid\\s+([^;]+);");
    QRegularExpressionMatch match = regex.match(estiloAtual);

    if (match.hasMatch()) {
        corBorda = match.captured(1); // Captura a cor da borda atual
    }

    // Define o novo estilo mantendo a borda e alterando apenas o background-color
    QString novoEstilo = QString("background-color: yellow; border-radius: 10px; border: 2px solid %1;").arg(corBorda);
    botoes[row][col]->setStyleSheet(novoEstilo);

}

// Método para marcar o botão correspondente
void Tabuleiro::marcarProprio(int row, int col) {
    QString estiloAtual = botoes[row][col]->styleSheet(); // Pega o estilo atual
    QString corAtual = "lightgray"; // Valor padrão caso não encontre a cor

    // Expressão regular para encontrar a cor de fundo no estilo atual
    QRegularExpression regex("background-color:\\s*([^;]+);");
    QRegularExpressionMatch match = regex.match(estiloAtual);

    if (match.hasMatch()) {
        corAtual = match.captured(1); // Captura a cor de fundo atual
    }

    // Define o novo estilo mantendo a cor e alterando apenas a borda
    QString novoEstilo = QString("background-color: %1; border-radius: 10px; border: 2px solid red;").arg(corAtual);
    botoes[row][col]->setStyleSheet(novoEstilo);
}

// Retorna true se um botão foi clicado
bool Tabuleiro::isBotaoClicado() const {
    return botaoClicado;
}

// Reseta a variável de clique no início de cada turno
void Tabuleiro::resetarClique() {
    botaoClicado = false;
}

int Tabuleiro::getLinhaBotao() const {
    return linha;
}

char Tabuleiro::getColunaBotao() const {
    return coluna;
}

QPushButton* Tabuleiro::getBotao(int linha, int coluna) {
    if (linha < 0 || linha >= 10 || coluna < 0 || coluna >= 10) {
        return nullptr;
    }
    return botoes[linha][coluna];
}

