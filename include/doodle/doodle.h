#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
enum class Direction { RIGHT, LEFT, STAND};
class Doodle: public QGraphicsPixmapItem
{
public slots:
    void onJumpFinished();
public:
    Direction move = Direction::STAND;
    bool isJumping = true;
    double verticalVelocity;
    const double jumpForce = 20.0; // Сила прыжка
    const double gravity = 1;     // Гравитация
    Doodle(int x, int y, QGraphicsScene* scene);
};
