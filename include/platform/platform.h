#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Platform : public QGraphicsPixmapItem {
    QPixmap* image;
public:
    Platform(int x, int y, QGraphicsScene* scene);
    ~Platform();
};
