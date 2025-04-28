#include "doodle.h"
#include <QDebug>
Doodle::Doodle(int x, int y, QGraphicsScene* scene) {
    doodleSprite = new QPixmap("../../assets/102.jpg");
    if (doodleSprite->isNull()) {
        qCritical() << "No doodle sprite found.";
        throw std::logic_error("Gameplay is unplayable");
    } else {
        ghost = new QGraphicsPixmapItem(*doodleSprite);
        setPixmap(*doodleSprite);
        ghost->setPixmap(*doodleSprite);
        setPos(x, y);
        ghost->setPos(-doodleSprite->width(), -doodleSprite->height());
    }
    scene->addItem(this);
    scene->addItem(ghost);
}

void Doodle::updatePosition() {
    if (toRight) {
        moveBy(10, 0);
        if(x()+doodleSprite->width() > 512)
        {
            isTeleporting = true;
            ghost->setPos(x()-512,y());
        }
        if(isTeleporting) {
            ghost->moveBy(10,0);
        }
        if(x() >= 512) {
            setPos(ghost->pos());
            ghost->setPos(-doodleSprite->width(), -doodleSprite->height());
            isTeleporting = false;
        }
    } else if (toLeft) {
        moveBy(-10, 0);
        if(x() < 0) {
            isTeleporting = true;
            ghost->setPos(x()+512,y());
        }
        if(isTeleporting) {
            ghost->moveBy(-10,0);
        }
        if(x() <= -doodleSprite->width()) {
            setPos(ghost->pos());
            ghost->setPos(-doodleSprite->width(), -doodleSprite->height());
            isTeleporting = false;
        }
    }
}
