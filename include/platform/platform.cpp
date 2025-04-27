#include <QDebug>
#include "../platform/platform.h"
Platform::Platform(int x, int y, QGraphicsScene* scene, PlatType type):type(type) {
    if(type == PlatType::Normal) {
        image = new QPixmap("../../assets/platform.png");
    } else if (type == PlatType::TripleJump) {
        image = new QPixmap("../../assets/grass_4x1.png");
    }
    if (!image->isNull()) {
        setPixmap(*image);
        setPos(x, y);
    } else {
        qCritical() << "No platform sprite found.";
        throw std::logic_error("Gameplay is unplayable");
    }
    scene->addItem(this);
}
PlatType Platform::GetType() {
    return type;
}
