#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
class Doodle: public QGraphicsPixmapItem
{
public slots:
    void onJumpFinished();
public:
    int jumpOffset = 0;
    bool toRight = false;
    bool toLeft = false;
    bool isJumping = true;
    double verticalVelocity;
    const double jumpForce = 0.0; // Сила прыжка
    const double gravity = 0;     // Гравитация
    bool isTeleporting = false;
    Doodle(int x, int y, QGraphicsScene* scene);
};
