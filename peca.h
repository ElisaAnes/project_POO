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

    // Retorna se a peça está vertical ou não
    bool isPieceVertical() const;


    bool isVerticalPiece() const { return isVertical; } // Método para saber se a peça está em modo vertical

protected:
    int currentRow = 7; // Linha inicial
    int currentCol = 7; // Coluna inicial
    bool isVertical = false; // Indica a orientação da peça

    void keyPressEvent(QKeyEvent *event) override;

private:
    void rotatePiece();
};

#endif // PECA_H
