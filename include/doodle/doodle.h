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
    bool isJumping = true;
    double verticalVelocity;
    const double jumpForce = 20.0; // Сила прыжка
    const double gravity = 1;     // Гравитация
    Doodle(int x, int y, QGraphicsScene* scene);
};
