#include <QApplication>
#include "batalhanaval.h"
/*
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BatalhaNaval jogo;

    return app.exec();
}
*/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    BatalhaNaval jogo;
    jogo.iniciarJogo(); // 🔹 Agora o próprio jogo decide se será Servidor ou Cliente
    return app.exec();
}
