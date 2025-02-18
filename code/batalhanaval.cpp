#include "batalhanaval.h"

BatalhaNaval::BatalhaNaval(QObject *parent)
    : QObject(parent),
    peca1_1(), peca1_2(), peca1_3(),
    peca2_1(), peca2_2(), peca2_3(),
    acertos1(0),
    acertos2(0),
    turnoJogador1(true),
    fasePosicionamento(true)
{
    // Criando as janelas dos tabuleiros separadamente
    tabuleiro1 = new Tabuleiro({&peca1_1, &peca1_2, &peca1_3});
    tabuleiro2 = new Tabuleiro({&peca2_1, &peca2_2, &peca2_3});

    tabuleiro1->setWindowTitle("Tabuleiro do Jogador 1");
    tabuleiro2->setWindowTitle("Tabuleiro do Jogador 2");

    tabuleiro1->setTurnoAtivo(turnoJogador1);
    tabuleiro2->setTurnoAtivo(!turnoJogador1);

    // Exibir as duas janelas separadas
    tabuleiro1->show();
    tabuleiro2->show();

    configurarJogo();
}

void BatalhaNaval::configurarJogo() {
    connect(&turnoTimer, &QTimer::timeout, this, &BatalhaNaval::alternarTurno);
    turnoTimer.start(10000);
}


void BatalhaNaval::alternarTurno() {
    if (fasePosicionamento) {
        if (tabuleiro1->isPecasTravadas() && tabuleiro2->isPecasTravadas()) {
            qDebug() << "Ambos os jogadores travaram seus navios. O jogo começa agora!";
            fasePosicionamento = false;
            turnoTimer.start(10000);
        } else {
            qDebug() << "Aguardando ambos os jogadores posicionarem os navios...";
            return;
        }
    } else {
        turnoJogador1 = !turnoJogador1;
        tabuleiro1->setTurnoAtivo(turnoJogador1);
        tabuleiro2->setTurnoAtivo(!turnoJogador1);

        QObject::disconnect(tabuleiro1, nullptr, tabuleiro2, nullptr);
        QObject::disconnect(tabuleiro2, nullptr, tabuleiro1, nullptr);

        Tabuleiro *tabuleiroAtivo = turnoJogador1 ? tabuleiro2 : tabuleiro1;
        Tabuleiro *tabuleiroOponente = turnoJogador1 ? tabuleiro1 : tabuleiro2;

        Peca &peca1 = turnoJogador1 ? peca1_1 : peca2_1;
        Peca &peca2 = turnoJogador1 ? peca1_2 : peca2_2;
        Peca &peca3 = turnoJogador1 ? peca1_3 : peca2_3;

        int &acertos = turnoJogador1 ? acertos1 : acertos2;

        if (tabuleiroAtivo->verificarAcerto(peca1) || tabuleiroAtivo->verificarAcerto(peca2) || tabuleiroAtivo->verificarAcerto(peca3)) {
            qDebug() << "Acertou o navio!";
            acertos++;

            QLabel *imagemLabel = new QLabel(tabuleiroAtivo);
            QPixmap imagem(":/bomba.png");
            imagemLabel->setPixmap(imagem);
            imagemLabel->setScaledContents(true);
            imagemLabel->setGeometry(75, 75, 500, 500);
            imagemLabel->show();

            QTimer::singleShot(3000, imagemLabel, [imagemLabel]() {
                imagemLabel->hide();
                imagemLabel->deleteLater();
            });

        } else {
            qDebug() << "Errou o navio!";
            QLabel *imagemLabel = new QLabel(tabuleiroAtivo);
            QPixmap imagem(":/agua.png");
            imagemLabel->setPixmap(imagem);
            imagemLabel->setScaledContents(true);
            imagemLabel->setGeometry(75, 150, 500, 250);
            imagemLabel->show();

            QTimer::singleShot(3000, imagemLabel, [imagemLabel]() {
                imagemLabel->hide();
                imagemLabel->deleteLater();
            });
        }

        if (acertos == 6) {
            qDebug() << "Fim de jogo! O Jogador " << (turnoJogador1 ? 1 : 2) << " venceu!";
            QApplication::quit();
        }

        tabuleiroAtivo->resetarClique();

        // 🔥 **Correção: agora marca o próprio tabuleiro e o do adversário!**
        QObject::connect(tabuleiroAtivo, &Tabuleiro::buttonClicked, tabuleiroOponente, &Tabuleiro::marcarBotao);
        QObject::connect(tabuleiroAtivo, &Tabuleiro::buttonClicked, tabuleiroAtivo, &Tabuleiro::marcarProprio);
    }
}//
