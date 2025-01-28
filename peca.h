#ifndef PECA_H
#define PECA_H

#include <QPushButton>
#include <QMouseEvent>

class Peca : public QPushButton {
    Q_OBJECT

public:
    explicit Peca(QWidget *parent = nullptr);

protected:
    bool dragging = false;  // Indica se a peça está sendo arrastada
    QPoint dragStartPos;    // Posição inicial do mouse durante o arraste
    bool isVertical = false; // Indica a orientação da peça (horizontal ou vertical)

    // Eventos do mouse
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void rotatePiece(); // Método para rotacionar a peça
};

#endif // PECA_H
