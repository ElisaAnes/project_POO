#include "peca.h"

Peca::Peca(QWidget *parent) : QPushButton(parent) {
    setFixedSize(80, 20); // Define o tamanho inicial da peça
    setStyleSheet("background-color: blue; color: white; border-radius: 10px;"); // Estilo da peça
    setFocusPolicy(Qt::StrongFocus); // Permite que o widget receba eventos de teclado
}

void Peca::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        toggleLock(); // Alterna o estado de travamento ao clicar
    }
}

void Peca::toggleLock() {
    locked = !locked; // Alterna entre travado e destravado

    // Atualiza a cor da peça para indicar o estado (azul = movível, vermelho = travado)
    if (locked) {
        setStyleSheet("background-color: red; color: white; border-radius: 10px;");

        // Converte o número da coluna para uma letra (A-J)
        coluna = 'A' + (currentCol - 1);
        linha = currentRow;

        // Declara variáveis antes do if para estarem acessíveis após ele
        coluna2 = coluna;
        linha2 = linha;

        if (isPieceVertical() == true) {
           linha2 = currentRow + 1;
        }else{
           coluna2= coluna + 1;
        }

        // Exibe a posição da peça no terminal
        qDebug() << "Peça travada nas posições: (" << coluna << "," << linha << ") e (" << coluna2 << "," << linha2 << ")";
    } else {
        setStyleSheet("background-color: blue; color: white; border-radius: 10px;");
    }
}


void Peca::keyPressEvent(QKeyEvent *event) {

    if (locked) {
        return; // Se a peça estiver travada, não faz nada
    }

    switch (event->key()) {
    case Qt::Key_Up:
        if (currentRow > 1) {
            currentRow--;
        }
        break;
    case Qt::Key_Down:

        if (isPieceVertical() == true) {
            if (currentRow < 9) {
                currentRow++;
            }
        } else {
            if (currentRow < 10) {
                currentRow++;
            }
        }
        break;
    case Qt::Key_Left:
        if (currentCol > 1) {
            currentCol--;
        }
        break;
    case Qt::Key_Right:

        if (isPieceVertical() == true) {
            if (currentCol < 10) {
                currentCol++;
            }
        } else {
            if (currentCol < 9) {
                currentCol++;
            }
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

// Métodos para obter as posições da peça
int Peca::getLinha() const{
    return linha;
}

int Peca::getLinha2() const{
    return linha2;
}

char Peca::getColuna() const{
    return coluna;
}

char Peca::getColuna2() const{
    return coluna2;
}
