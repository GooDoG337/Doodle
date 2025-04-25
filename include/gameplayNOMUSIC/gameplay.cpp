#include "gameplay.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <random>
#include "../platform/platform.h"
#include "../background/background.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
#include <QRandomGenerator>
Gameplay::Gameplay(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), sceneWidth(512), sceneHeight(512) {
    // Установка размеров окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSceneRect(0, 0, sceneWidth, sceneHeight);
    Background bckgrnd(this);
    //Настраиваем фпс
    fpsTimer = new QTimer(this);
    colisionTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    connect(colisionTimer, &QTimer::timeout, this, &Gameplay::checkCollison);
    connect(this, &Gameplay::newParty, this, &Gameplay::newCreation);
    jumpscore = new Score(this);
    fpsTimer->start(16); // Обновляем каждые 16 миллисекунд (примерно 60 FPS)
    colisionTimer->start(1);
    connect(this, &Gameplay::jumpFinished, this, &Gameplay::onJumpFinished);
    //Ебашим платформу
    doodle = new Doodle(256,256, scene);
    platforms.append(new Platform(256,256+32,scene));
    spawnPlatformsReborn(spawnPlatformsReborn(height(),-height()));
    setScene(scene);
}

void Gameplay::checkCollison() {
    for (Platform* platform : platforms) {
        QRect doodleRect(doodle->x(), doodle->y(), doodle->pixmap().width(), doodle->pixmap().height());  // Bottom part of the doodle
        QRect platformRect(platform->x(), platform->y(), platform->pixmap().width(), platform->pixmap().height());
        if (doodleRect.intersects(platformRect) && Power < 0) {
            Power = 20;
            break;
        }
    }
}
void Gameplay::updateDoodlePosition() {
    if(platforms.isEmpty()) {
        jumpscore->itsOver();
    }
    if (doodle->toRight) {
        doodle->moveBy(10, 0); // Двигаем doodle вправо
    }
    else if (doodle->toLeft) {
        doodle->moveBy(-10, 0); // Двигаем doodle влево
    }
    for(Platform* platform:platforms) {
        platform->moveBy(0,Power);
    }
    Power-=Gravity;
    if(Power>0)
    {
        jumpscore->add(Power);
        highet+=Power;
    }
    if(highet>= height()) {
        highet = 0;
        jumpscore->add();
        emit newParty();
    }
    for(int i = 0; i < platforms.size(); i++) {
        if(platforms[i]->y() > height()) {
            platforms[i]->hide();
            platforms.erase(platforms.begin()+i);
        }
    }
}

void Gameplay::newCreation() {
    spawnPlatformsReborn(spawnPlatformsReborn(0, -height()));
}
void Gameplay::onJumpFinished() {
    doodle->isJumping = true;
    Power = 20;
}

void Gameplay::makePause(){
    if(!pause) {
    disconnect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    pause = true;
    } else {
        connect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
        pause = false;
    }
}
void Gameplay::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Right:
        doodle->toRight = true;
        break;
    case Qt::Key_Left:
        doodle->toLeft = true;
        break;
    case Qt::Key_Escape:
        makePause();
    default:
        QGraphicsView::keyPressEvent(event); // Обработка других событий клавиатуры
    }
}


int Gameplay::spawnPlatformsReborn(int startHigh, int startLow) {
    int jumpHeight = 210;
    int high_pos = startHigh;
    int realWidth = width()-platforms[0]->pixmap().width();
    while(high_pos > startLow)
    {
        int y_pos = high_pos-QRandomGenerator::global()->bounded(190, jumpHeight);
        int x_pos = QRandomGenerator::global()->bounded(0, realWidth);
        platforms.append( new Platform(x_pos, y_pos, scene));
        high_pos=y_pos;
    }
    return high_pos;
}
void Gameplay::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Right:
        doodle->toRight = false;
        break;
    case Qt::Key_Left:
        doodle->toLeft = false;
        break;
    default:
        QGraphicsView::keyReleaseEvent(event);
    }
}
