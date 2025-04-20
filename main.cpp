#include <QApplication>
#include "include/gameplay/gameplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gameplay window;
    window.show();
    return a.exec();
}
