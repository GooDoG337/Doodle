#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
class Doodle: public QGraphicsPixmapItem
{
public slots:
    void onJumpFinished();
public:
    bool toRight = false;
    bool toLeft = false;
    bool isTeleporting = false;
    Doodle(int x, int y, QGraphicsScene* scene);
    void updatePosition();
    QGraphicsPixmapItem* ghost;
    QPixmap* doodleSprite;
};
