#include <QApplication>
#include "include/gameplay/gameplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gameplay window;
    return a.exec();
}

//Теперь тут есть ЛАДА (QLabel), которая "едет" направо/налево, и якобы прыгает.
//Управление:   Enter - "прыжок?"
//              Стрелка направо - "езда? направо"
//              Стрелка налево - "езда? налево"
