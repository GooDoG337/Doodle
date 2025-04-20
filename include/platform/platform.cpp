#include <QPixmap>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../platform/platform.h"
Platform::Platform(int x, int y, QGraphicsScene* scene) {
    QPixmap pixmap("../../assets/platform.png");
    if (pixmap.isNull()) {
        qDebug() << "Failed to load pixmap";
    } else {
        setPixmap(pixmap);
        int initialX = x;
        int initialY = y;
        setPos(initialX, initialY);
    }
    scene->addItem(this);
}
