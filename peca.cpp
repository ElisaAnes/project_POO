#include "peca.h"

Peca::Peca(QWidget *parent) : QPushButton(parent) {
    setFixedSize(80, 20); // Define o tamanho inicial da peça
    setStyleSheet("background-color: blue; color: white; border-radius: 10px;"); // Estilo da peça
    setCursor(Qt::OpenHandCursor); // Cursor de mão aberta ao passar o mouse
}

void Peca::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Inicia o arraste
        dragging = true;
        dragStartPos = event->globalPosition().toPoint();
        setCursor(Qt::ClosedHandCursor); // Cursor de mão fechada
    } else if (event->button() == Qt::RightButton) {
        // Rotaciona a peça ao clicar com o botão direito
        rotatePiece();
    }
}

void Peca::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Calcula o deslocamento do mouse
        QPoint offset = event->globalPosition().toPoint() - dragStartPos;
        move(pos() + offset); // Move a peça para a nova posição
        dragStartPos = event->globalPosition().toPoint(); // Atualiza a posição inicial do mouse
    }
}

void Peca::mouseReleaseEvent(QMouseEvent *event) {
    if (dragging && event->button() == Qt::LeftButton) {
        dragging = false; // Finaliza o arraste
        setCursor(Qt::OpenHandCursor); // Volta para o cursor de mão aberta
    }
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
