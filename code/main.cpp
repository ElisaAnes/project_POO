#include "battleship.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Battleship w;
    w.show();
    return a.exec();
}
