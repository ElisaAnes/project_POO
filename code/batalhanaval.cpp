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
    // Certifique-se de inicializar os tabuleiros
    tabuleiro1 = new Tabuleiro({&peca1_1, &peca1_2, &peca1_3});
    tabuleiro2 = new Tabuleiro({&peca2_1, &peca2_2, &peca2_3});

    if (!tabuleiro1 || !tabuleiro2) {
        qDebug() << "Erro: Falha ao inicializar os tabuleiros!";
        return;
    }

    tabuleiro1->setWindowTitle("Tabuleiro do Jogador 1");
    tabuleiro2->setWindowTitle("Tabuleiro do Jogador 2");

    tabuleiro1->setTurnoAtivo(turnoJogador1);
    tabuleiro2->setTurnoAtivo(!turnoJogador1);

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

            turnoJogador1 = true;
            turnoTimer.start(10000);

            return;
        } else {
            qDebug() << "Aguardando ambos os jogadores posicionarem os navios...";
            return;
        }
    }

    turnoJogador1 = !turnoJogador1;
    tabuleiro1->setTurnoAtivo(turnoJogador1);
    tabuleiro2->setTurnoAtivo(!turnoJogador1);

    QObject::disconnect(tabuleiro1, nullptr, tabuleiro2, nullptr);
    QObject::disconnect(tabuleiro2, nullptr, tabuleiro1, nullptr);

    // 🔹 O jogador ataca o tabuleiro do oponente
    Tabuleiro *tabuleiroJogador = turnoJogador1 ? tabuleiro1 : tabuleiro2;
    Tabuleiro *tabuleiroOponente = turnoJogador1 ? tabuleiro2 : tabuleiro1;

    Peca *pecas[3] = {turnoJogador1 ? &peca1_1 : &peca2_1,
                      turnoJogador1 ? &peca1_2 : &peca2_2,
                      turnoJogador1 ? &peca1_3 : &peca2_3};

    int &acertos = turnoJogador1 ? acertos1 : acertos2;

    int linhaAtacada = tabuleiroOponente->getLinhaBotao();
    char colunaAtacada = tabuleiroOponente->getColunaBotao();

    // 🔹 Verifica acerto no tabuleiro do oponente
    bool acerto = verificarAcerto(tabuleiroOponente, pecas, 3);

    if (tabuleiroJogador && tabuleiroOponente) {
        if (acerto) {
            qDebug() << "Acertou o navio!";
            acertos++;

            // 🔹 No tabuleiro do JOGADOR, aparece explosão onde ele atacou
            marcarAtaqueNoTabuleiro(tabuleiroJogador, linhaAtacada, colunaAtacada, ":/atingido.png");

            // 🔹 No tabuleiro do OPONENTE, aparece que o navio foi atingido
            marcarAtaqueNoTabuleiro(tabuleiroOponente, linhaAtacada, colunaAtacada, ":/bomba.png");

        } else {
            qDebug() << "Errou o navio!";

            // 🔹 No tabuleiro do JOGADOR, aparece água onde ele atacou (corrigido!)
            marcarAtaqueNoTabuleiro(tabuleiroOponente, linhaAtacada, colunaAtacada, ":/agua.png");

            // 🔹 No tabuleiro do OPONENTE, nada muda agora!
        }

        if (acertos == 6) {
            qDebug() << "Fim de jogo! O Jogador " << (turnoJogador1 ? 1 : 2) << " venceu!";
            QApplication::quit();
        }

        tabuleiroJogador->resetarClique();
        QObject::connect(tabuleiroJogador, &Tabuleiro::buttonClicked, tabuleiroOponente, &Tabuleiro::marcarBotao);
        QObject::connect(tabuleiroJogador, &Tabuleiro::buttonClicked, tabuleiroJogador, &Tabuleiro::marcarProprio);
    } else {
        qDebug() << "Erro: tabuleiroJogador ou tabuleiroOponente são nullptr!";
    }
}



void BatalhaNaval::marcarAtaqueNoTabuleiro(Tabuleiro *tabuleiro, int linha, char coluna, const QString &caminhoImagem) {
    int colIndex = coluna - 'A'; // Converte 'A'..'J' para 0..9

    QPushButton *botao = tabuleiro->getBotao(linha - 1, colIndex);
    if (!botao) {
        qDebug() << "Erro: Botão inválido no tabuleiro!";
        return;
    }

    QPixmap imagem(caminhoImagem);
    QIcon icone(imagem.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    botao->setIcon(icone);
    botao->setIconSize(QSize(30, 30)); // 🔹 Ajusta o tamanho da imagem dentro do botão
}




bool BatalhaNaval::verificarAcerto(Tabuleiro *tabuleiro, Peca *pecas[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        if (tabuleiro->verificarAcerto(*pecas[i])) {
            return true;
        }
    }
    return false;
}

void BatalhaNaval::mostrarImagem(Tabuleiro *tabuleiro, const QString &caminhoImagem, int x, int y, int largura, int altura) {
    QLabel *imagemLabel = new QLabel(tabuleiro);
    QPixmap imagem(caminhoImagem);
    imagemLabel->setPixmap(imagem);
    imagemLabel->setScaledContents(true);
    imagemLabel->setGeometry(x, y, largura, altura);
    imagemLabel->show();

    QTimer::singleShot(3000, imagemLabel, [imagemLabel]() {
        imagemLabel->hide();
        imagemLabel->deleteLater();
    });
}
