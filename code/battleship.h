#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <QMainWindow>

class Battleship : public QMainWindow
{
    Q_OBJECT

public:
    Battleship(QWidget *parent = nullptr);
    ~Battleship();
};
#endif // BATTLESHIP_H
