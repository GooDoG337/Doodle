#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Platform : public QGraphicsPixmapItem {
public:
    Platform(int x, int y, QGraphicsScene* scene);
};
