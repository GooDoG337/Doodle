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
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), doodle(nullptr), sceneWidth(512), sceneHeight(512) {
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
    doodle = new Doodle(256,512-64, scene);
    platforms.append(new Platform(256,512-32,scene));
    QTextStream out(stdout);
    out << spawnPlatformsReborn(spawnPlatformsReborn(height()*4)) << '\n';

    setScene(scene);
}

void Gameplay::checkCollison() {
    for (Platform* platform : platforms) {
        QRect doodleRect(doodle->x(), doodle->y(), doodle->pixmap().width(), doodle->pixmap().height());  // Bottom part of the doodle
        QRect platformRect(platform->x(), platform->y(), platform->pixmap().width(), doodle->pixmap().height());
        if (doodleRect.intersects(platformRect) && doodle->verticalVelocity < 0) {
            jumpscore->add();
            emit onJumpFinished();
            break;
        }
    }
}
void Gameplay::updateDoodlePosition() {
    if (doodle->toRight) {
        doodle->moveBy(10, 0); // Двигаем doodle вправо
    }
    else if (doodle->toLeft) {
        doodle->moveBy(-10, 0); // Двигаем doodle влево
    }

    if (doodle->isJumping) {
        doodle->verticalVelocity -= doodle->gravity; // Применяем гравитацию
        doodle->moveBy(0, -doodle->verticalVelocity);
        highet+= doodle->verticalVelocity;
        if(doodle->verticalVelocity > 0 && width()/2-doodle->y() > 64) {
        for(Platform* platform:platforms) {
            platform->moveBy(0,doodle->verticalVelocity);
        }
    }
        if(highet>= height())
    {
        highet = 0;
        emit newParty();
    }
        for(int i = 0; i < platforms.size(); i++) {
            if(platforms[i]->y() > height()) {
                platforms[i]->hide();
                platforms.erase(platforms.begin()+i);
            }
        }
}
}

void Gameplay::newCreation() {
    spawnPlatformsReborn(spawnPlatformsReborn(height()*2));

}
void Gameplay::onJumpFinished() {
        doodle->isJumping = true;
        doodle->verticalVelocity = doodle->jumpForce;
}

void Gameplay::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Right:
        doodle->toRight = true;
        break;
    case Qt::Key_Left:
        doodle->toLeft = true;
        break;
    default:
        QGraphicsView::keyPressEvent(event); // Обработка других событий клавиатуры
    }
}

/*void Gameplay::spawnPlatforms(int high, int num, bool stealth)
{
    for (int i = 0; i < num; ++i) {
        if(!stealth)
        {
            platforms.append( new Platform(QRandomGenerator::global()->bounded(0, width()), QRandomGenerator::global()->bounded(-high, height()), scene));
        } else {
            int y_pos = QRandomGenerator::global()->bounded(int(-2*high-doodle->jumpForce), 2*int(doodle->jumpForce));
            int x_pos = QRandomGenerator::global()->bounded(0, width());
            platforms.append( new Platform(x_pos, y_pos, scene));
        }
    }
}*/
int Gameplay::spawnPlatformsReborn(int startHigh) {
    int jumpHeight = 210;
    int high_pos = startHigh;
    int realWidth = width()-platforms[0]->pixmap().width();
    while(high_pos > 0)
    {
        int y_pos = high_pos-QRandomGenerator::global()->bounded(0, jumpHeight);
        int x_pos = QRandomGenerator::global()->bounded(platforms[0]->pixmap().width(), realWidth);
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
