#include "doodle.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
Doodle::Doodle(int x, int y, QGraphicsScene* scene) {
    QPixmap doodlePixmap("../../assets/ladapriora.jpg");
    if (doodlePixmap.isNull()) {
        qDebug() << "Failed to load doodle image!";
    } else {
        setPixmap(doodlePixmap);
        setPos(x, y);
    }
    scene->addItem(this);
}
