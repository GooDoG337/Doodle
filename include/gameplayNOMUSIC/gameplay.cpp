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
#include <QLabel>
Gameplay::Gameplay(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), sceneWidth(512), sceneHeight(512) {
    // Установка размеров окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(512,512);
    setSceneRect(0, 0, sceneWidth, sceneHeight);
    Background bckgrnd(this);
    fpsTimer = new QTimer(this);
    colisionTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    connect(colisionTimer, &QTimer::timeout, this, &Gameplay::checkCollison);
    connect(this, &Gameplay::newParty, this, &Gameplay::newCreation);
    jumpscore = new Score(this);
    fpsTimer->start(16);
    colisionTimer->start(1);
    connect(this, &Gameplay::jumpFinished, this, &Gameplay::onJumpFinished);
    //Ебашим платформу
    doodle = new Doodle(256,200, scene);
    platforms.append(new Platform(256,216,scene, PlatType::Normal));
    spawnPlatformsReborn(spawnPlatformsReborn(platforms[0]->y(),-height()));

    doodle_clone = new QGraphicsPixmapItem(QPixmap("../../assets/ladapriora.jpg"));
    doodle_clone->setPos(-doodle_clone->pixmap().width(), -doodle_clone->pixmap().height());
    scene->addItem(doodle_clone);
    connect(jumpscore, &Score::scoreZero, this, &Gameplay::makeStop);
    setScene(scene);

    pauseMenuLabel = new QLabel(this);
    pauseMenuLabel->setText("PAUSED");
    pauseMenuLabel->setAlignment(Qt::AlignCenter);
    pauseMenuLabel->setStyleSheet("background-color: rgba(0, 0, 0, 150); color: white; font-size: 32px;");
    pauseMenuLabel->setGeometry(0, 0, width(), height());
    pauseMenuLabel->hide();

    stopMenuLabel = new QLabel(this);
    stopMenuLabel->setText("GAME OVER");
    stopMenuLabel->setAlignment(Qt::AlignCenter);
    stopMenuLabel->setStyleSheet("background-color: rgba(255, 0, 0, 150); color: white; font-size: 36px;");
    stopMenuLabel->setGeometry(0, 0, width(), height());
    stopMenuLabel->hide();
}

void Gameplay::checkCollison() {
    for (Platform* platform : platforms) {
        QRect doodleRect(doodle->x(), doodle->y()+75, doodle->pixmap().width(), 3);  // Bottom part of the doodle
        QRect doodle_cloneRect(doodle_clone->x(), doodle_clone->y()+75, doodle_clone->pixmap().width(), 3);
        QRect platformRect(platform->x(), platform->y(), platform->pixmap().width(), platform->pixmap().height());
        if ((doodleRect.intersects(platformRect) || doodle_cloneRect.intersects(platformRect)) && Power < 0) {
            if(platform->GetType() == PlatType::Normal)
            {
                Power = 20;
            } else if (platform->GetType() == PlatType::TripleJump)
            {
                Power = 60;
            }
            break;
        }
    }
}
void Gameplay::updateDoodlePosition() {
    if(platforms.isEmpty()) {
        jumpscore->itsOver();
    }
    if (doodle->toRight) {
        if(doodle->x()+doodle->pixmap().width() > 512)
        {
            doodle->isTeleporting = true;
            doodle_clone->setPos(doodle->x()-512,doodle->y());
        }
        doodle->moveBy(10, 0); // Двигаем doodle вправо
        if(doodle->isTeleporting) {
            doodle_clone->moveBy(10,0);
        }
        if(doodle->x() >= 512) {
            doodle->setPos(doodle_clone->pos());
            doodle_clone->setPos(-doodle_clone->pixmap().width(), -doodle_clone->pixmap().height());
            doodle->isTeleporting = false;
        }
    }
    else if (doodle->toLeft) {
        if(doodle->x() < 0) {
            doodle->isTeleporting = true;
            doodle_clone->setPos(doodle->x()+512,doodle->y());
        }
        doodle->moveBy(-10, 0); // Двигаем doodle вправо
        if(doodle->isTeleporting) {
            doodle_clone->moveBy(-10,0);
        }
        if(doodle->x() <= -doodle->pixmap().width()) {
            doodle->setPos(doodle_clone->pos());
            doodle_clone->setPos(-doodle_clone->pixmap().width(), -doodle_clone->pixmap().height());
            doodle->isTeleporting = false;
        }
    }
    for(Platform* platform:platforms) {
        platform->moveBy(0,Power);
    }
    jumpscore->add(Power);
    highet+=Power;
    Power-=Gravity;
    if(highet>= height()) {
        highet = doodle->y();
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
    spawnPlatformsReborn(spawnPlatformsReborn(platforms[platforms.size()-1]->y(), -height()));
}

void Gameplay::onJumpFinished() {
    doodle->isJumping = true;
    Power = 20;
}

void Gameplay::makePause(){
    if(!pause) {
    disconnect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    pause = true;
    pauseMenuLabel->show();
    } else {
        connect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
        pause = false;
        pauseMenuLabel->hide();
    }
}

void Gameplay::makeStop() {
    for(int i = 0; i < platforms.size(); i++) {
            platforms[i]->hide();
            platforms.erase(platforms.begin()+i);
    }
    disconnect(fpsTimer, &QTimer::timeout, this, &Gameplay::updateDoodlePosition);
    disconnect(colisionTimer, &QTimer::timeout, this, &Gameplay::checkCollison);
    stopMenuLabel->show();
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


int Gameplay::spawnPlatformsReborn(int startLow, int startHigh) {
    int jumpHeight = 210;
    int height_pos = startLow;
    int realWidth = width()-platforms[0]->pixmap().width();
    while(height_pos > startHigh)
    {
        PlatType type = PlatType::Normal;
        if(QRandomGenerator::global()->bounded(0,40) == 0) {
            type = PlatType::TripleJump;
        }
        int y_pos = height_pos-jumpHeight;
        int x_pos = QRandomGenerator::global()->bounded(0, 342);
        platforms.append( new Platform(x_pos, y_pos, scene, type));
        height_pos=y_pos;
    }
    return height_pos;
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
