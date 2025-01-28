#ifndef PECA_H
#define PECA_H

#include <QPushButton>
#include <QKeyEvent>

class Peca : public QPushButton {
    Q_OBJECT

public:
    explicit Peca(QWidget *parent = nullptr);

    // Métodos para obter e definir a posição da peça no layout
    int getRow() const { return currentRow; }
    int getCol() const { return currentCol; }
    void setPosition(int row, int col) { currentRow = row; currentCol = col; }

protected:
    int currentRow = 7; // Linha inicial
    int currentCol = 7; // Coluna inicial
    bool isVertical = false; // Indica a orientação da peça (horizontal ou vertical)

    void keyPressEvent(QKeyEvent *event) override; // Evento para capturar teclas

private:
    void rotatePiece(); // Método para rotacionar a peça
};


#endif // PECA_H
