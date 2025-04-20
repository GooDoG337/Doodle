#include "background.h"
#include <QPixmap>
#include <QGraphicsView>
#include <QDebug>
Background::Background(QGraphicsView* scene) {
    QPixmap background("../../assets/background.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image!";
    } else {
        scene->setBackgroundBrush(background.scaled(scene->size(), Qt::IgnoreAspectRatio));
    }
}
