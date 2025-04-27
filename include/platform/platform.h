#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
enum class PlatType {Normal, TripleJump};
class Platform : public QGraphicsPixmapItem {
    PlatType type;
    QPixmap* image;
public:
    PlatType GetType();
    Platform(int x, int y, QGraphicsScene* scene, PlatType PlatType = PlatType::Normal);
};
