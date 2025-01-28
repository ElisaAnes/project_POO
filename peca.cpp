#include "peca.h"

Peca::Peca(QWidget *parent) : QPushButton(parent) {
    setFixedSize(80, 20); // Define o tamanho inicial da peça
    setStyleSheet("background-color: blue; color: white; border-radius: 10px;"); // Estilo da peça
    setFocusPolicy(Qt::StrongFocus); // Permite que o widget receba eventos de teclado
}

void Peca::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        if (currentRow > 1) {
            currentRow--;
        }
        break;
    case Qt::Key_Down:
        if (currentRow < 10) {
            currentRow++;
        }
        break;
    case Qt::Key_Left:
        if (currentCol > 1) {
            currentCol--;
        }
        break;
    case Qt::Key_Right:
        if (currentCol < 9) {
            currentCol++;
        }
        break;
    case Qt::Key_R:
        rotatePiece(); // Rotaciona a peça
        break;
    default:
        QPushButton::keyPressEvent(event); // Passa o evento para o botão base
        return;
    }
    emit clicked(); // Atualiza a posição no layout
}

void Peca::rotatePiece() {
    if (isVertical) {
        // Rotaciona para a orientação horizontal
        setFixedSize(80, 20);
    } else {
        // Rotaciona para a orientação vertical
        setFixedSize(20, 80);
    }
    isVertical = !isVertical; // Alterna o estado de orientação
}

// Método para retornar se a peça está vertical ou não
bool Peca::isPieceVertical() const {
    return isVertical;
}
