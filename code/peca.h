#ifndef PECA_H
#define PECA_H

#include <QPushButton>
#include <QKeyEvent>

class Peca : public QPushButton {
    Q_OBJECT

public:
    explicit Peca(QWidget *parent = nullptr);

    // Métodos para obter informações da peça
    int getRow() const { return currentRow; }
    int getCol() const { return currentCol; }
    void setPosition(int row, int col) { currentRow = row; currentCol = col; }
    bool isPieceVertical() const;
    bool isLocked() const { return locked; } // Verifica se a peça está travada
    void imprimirPosicaoClique(int row, int col); // Imprime a posição do clique
    int getLinha() const; // Retorna a linha principal da peça
    int getLinha2() const; // Retorna a segunda linha se for vertical
    char getColuna() const; // Retorna a coluna principal da peça
    char getColuna2() const; // Retorna a segunda coluna se for horizontal


protected:
    int currentRow = 7;  // Linha inicial da peça no tabuleiro
    int currentCol = 7;  // Coluna inicial da peça no tabuleiro
    bool isVertical = false; // Indica a orientação da peça (horizontal ou vertical)
    bool locked = false; // Indica se a peça está travada

    void keyPressEvent(QKeyEvent *event) override;  // Captura teclas para mover a peça
    void mousePressEvent(QMouseEvent *event) override;  // Captura clique do mouse para travar/destravar a peça
    void toggleLock(); // Alterna entre travado/destravado

private:
    void rotatePiece(); // Método para rotacionar a peça ao pressionar "R"
    int linha, linha2; // Guarda a posição vertical da peça
    char coluna, coluna2; // Guarda a posição horizontal da peça
};

#endif // PECA_H
