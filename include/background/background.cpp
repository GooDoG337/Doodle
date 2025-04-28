#include "background.h"
#include <QDebug>
Background::Background(QGraphicsView* scene) {
    QPixmap background("../../assets/20yanvar.jpg");
    if (background.isNull()) {
        qWarning() << "No background.png found.";
    } else {
        scene->setBackgroundBrush(background.scaled(scene->size(), Qt::IgnoreAspectRatio));
    }
}
