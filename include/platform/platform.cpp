#include <QPixmap>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../platform/platform.h"
Platform::Platform(int x, int y, QGraphicsScene* scene) {
    image = new QPixmap("../../assets/platform.png");
    if (!image->isNull()) {
        setPixmap(*image);
        int initialX = x;
        int initialY = y;
        setPos(initialX, initialY);
    }
    scene->addItem(this);
}

Platform::~Platform() {
    hide();

}
