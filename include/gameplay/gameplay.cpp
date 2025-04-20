#include "gameplay.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <random>
#include "../platform/platform.h"
#include "../background/background.h"
#include "../doodle/doodle.h"
 #include <QRandomGenerator>
Gameplay::Gameplay(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), doodle(nullptr), sceneWidth(512), sceneHeight(512) {
    // Установка размеров окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSceneRect(0, 0, sceneWidth, sceneHeight);
    Background bckgrnd(this);
    //Настраиваем фпс
    fpsTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    connect(fpsTimer, &QTimer::timeout, this, &Gameplay::checkCollison);
    fpsTimer->start(16); // Обновляем каждые 16 миллисекунд (примерно 60 FPS)
    connect(this, &Gameplay::jumpFinished, this, &Gameplay::onJumpFinished);
    //Ебашим платформу
    doodle = new Doodle(128,128, scene);
    spawnPlatforms();
    setScene(scene);
}

void Gameplay::checkCollison() {
    for (Platform* platform : platforms) {
        QRect doodleRect(doodle->x(), doodle->y(), doodle->pixmap().width(), doodle->pixmap().height());  // Bottom part of the doodle
        QRect platformRect(platform->x(), platform->y(), platform->pixmap().width(), doodle->pixmap().height());
        if (doodleRect.intersects(platformRect) && doodle->verticalVelocity < 0) {
            doodle->isJumping = true;
            doodle->verticalVelocity = doodle->jumpForce;
            break;
        }
    }
}
void Gameplay::updateDoodlePosition() {
    if (doodle->move == Direction::RIGHT) {
        doodle->moveBy(5, 0); // Двигаем doodle вправо
    }
    else if (doodle->move == Direction::LEFT) {
        doodle->moveBy(-5, 0); // Двигаем doodle влево
    }

    if (doodle->isJumping) {
        doodle->verticalVelocity -= doodle->gravity; // Применяем гравитацию
        doodle->moveBy(0, -doodle->verticalVelocity);
        if(doodle->verticalVelocity > 0) {
        for(Platform* platform:platforms) {
            platform->moveBy(0,doodle->verticalVelocity);
        }
        // Проверяем, достиг ли doodle нижней границы
        /*if (doodle->y() >= height() - doodle->boundingRect().height()) {
            doodle->setPos(doodle->x(), height() - doodle->boundingRect().height());
            doodle->isJumping = false;
            doodle->verticalVelocity = 0;
            emit jumpFinished();
        }*/
    }
}
}
void Gameplay::onJumpFinished() {
        doodle->isJumping = true;
        doodle->verticalVelocity = doodle->jumpForce;
}

void Gameplay::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Right:
        doodle->move = Direction::RIGHT;
        break;
    case Qt::Key_Left:
        doodle->move = Direction::LEFT;
        break;
    default:
        QGraphicsView::keyPressEvent(event); // Обработка других событий клавиатуры
    }
}

void Gameplay::spawnPlatforms()
{
    for (int i = 0; i < 10; ++i) {
        platforms.append( new Platform(QRandomGenerator::global()->bounded(0, width()), QRandomGenerator::global()->bounded(0, height()), scene));
    }
}

void Gameplay::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Right:
    case Qt::Key_Left:
        doodle->move = Direction::STAND;
        break;
    default:
        QGraphicsView::keyReleaseEvent(event);
    }
}
