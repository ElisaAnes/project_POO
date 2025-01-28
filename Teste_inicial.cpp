// Importa as bibliotecas necessárias do Qt
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

// Declaração da classe Tabuleiro, derivada de QWidget
class Tabuleiro : public QWidget {
public:
    // Construtor da classe Tabuleiro
    Tabuleiro(QWidget *parent = nullptr) : QWidget(parent) {
        // Cria o layout em grade para organizar os widgets
        QGridLayout *layout = new QGridLayout(this);

        // Adiciona rótulos no topo do tabuleiro (letras de A a J)
        for (int col = 0; col < 10; ++col) {
            QLabel *letra = new QLabel(QString(QChar('A' + col)), this); // Cria um QLabel com a letra correspondente
            letra->setAlignment(Qt::AlignCenter); // Centraliza o texto do rótulo
            layout->addWidget(letra, 0, col + 1); // Adiciona o rótulo na linha 0, na coluna correspondente
        }

        // Adiciona rótulos na lateral esquerda do tabuleiro (números de 1 a 10)
        for (int row = 0; row < 10; ++row) {
            QLabel *numero = new QLabel(QString::number(row + 1), this); // Cria um QLabel com o número correspondente
            numero->setAlignment(Qt::AlignCenter); // Centraliza o texto do rótulo
            layout->addWidget(numero, row + 1, 0); // Adiciona o rótulo na coluna 0, na linha correspondente
        }

        // Adiciona os botões ao tabuleiro (10x10)
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                QPushButton *botao = new QPushButton(this); // Cria um botão
                botao->setFixedSize(20, 20); // Define o tamanho fixo do botão (largura e altura iguais para formar o círculo)
                botao->setStyleSheet("border-radius: 10px; border: 1px solid black; background-color: lightgray;"); // Aplica estilo de círculo
                layout->addWidget(botao, i + 1, j + 1); // Adiciona o botão na posição (i+1, j+1) na grade
                layout->setSpacing(40); // Define o espaçamento entre os widgets (10 pixels, por exemplo)

                // Garante que o botão fique acima da peça
                botao->raise(); // Eleva o botão sobre outros widgets
            }
        }

        // Cria uma peça para o tabuleiro
        QPushButton *peca = new QPushButton("", this); // Adiciona um ícone ou texto na peça
        peca->setFixedSize(80, 20); // Define o tamanho da peça
        peca->setStyleSheet("background-color: blue; color: white; border-radius: 10px;"); // Estilo da peça
        layout->addWidget(peca, 5, 5, 1, 2); // Posiciona a peça no tabuleiro (linha 5, coluna 5) ocupando 2 colunas
        peca->lower(); // Garante que a peça fique abaixo dos botões

        // Cria uma peça para o tabuleiro
        QPushButton *peca2 = new QPushButton("", this); // Adiciona um ícone ou texto na peça
        peca2->setFixedSize(140, 20); // Define o tamanho da peça
        peca2->setStyleSheet("background-color: red; color: white; border-radius: 10px;"); // Estilo da peça
        layout->addWidget(peca2, 4, 4, 1, 3); // Posiciona a peça no tabuleiro (linha 5, coluna 5) ocupando 2 colunas
        peca2->lower(); // Garante que a peça fique abaixo dos botões


        // Define o layout criado para o widget principal
        setLayout(layout);

        // Define o título da janela
        setWindowTitle("Batalha Naval");

        // Define o tamanho inicial da janela
        resize(600, 600);
    }
};

// Função principal que inicializa e executa a aplicação Qt
int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Cria a aplicação Qt, passando os argumentos da linha de comando

    Tabuleiro tabuleiro; // Cria uma instância do tabuleiro
    tabuleiro.show();    // Exibe o tabuleiro

    return app.exec();   // Entra no loop de execução da aplicação
}
