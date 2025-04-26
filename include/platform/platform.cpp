#include <QPixmap>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../platform/platform.h"
Platform::Platform(int x, int y, QGraphicsScene* scene, PlatType type):type(type) {
    if(type == PlatType::Normal) {
        image = new QPixmap("../../assets/platform.png");
    } else if (type == PlatType::TripleJump) {
        image = new QPixmap("../../assets/grass_4x1.png");
    }
    if (!image->isNull()) {
        setPixmap(*image);
        int initialX = x;
        int initialY = y;
        setPos(initialX, initialY);
    }
    scene->addItem(this);
}
PlatType Platform::GetType() {
    return type;
}
