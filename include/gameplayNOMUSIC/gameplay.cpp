#include "gameplay.h"
#include <QKeyEvent>
#include <QTimer>
#include "../platform/platform.h"
#include "../background/background.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
#include <QRandomGenerator>

Gameplay::Gameplay(QWidget* parent)
    : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sceneWidth,sceneHeight);
    setSceneRect(0, 0, sceneWidth, sceneHeight);
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Gameplay::updateMoves);
    connect(moveTimer, &QTimer::timeout, this, &Gameplay::checkCollison);
    connect(this, &Gameplay::newPlatformsNeeded, this, &Gameplay::newCreation);
    score = new Score(this);
    doodle = new Doodle(256,128, scene);
    platforms.append(new Platform(256,216,scene, PlatType::Normal));
    moveTimer->start(16);
    score->add(57);
    bckgrnd = new Background(this);
    spawnPlatformsReborn(spawnPlatformsReborn(platforms[0]->y(),-height()));
    connect(score, &Score::scoreZero, this, &Gameplay::makeStop);
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
    QRect doodleRect(doodle->x(), doodle->y()+75, doodle->pixmap().width(), 3);  // Bottom part of the doodle
    QRect doodle_ghostRect(doodle->ghost->x(), doodle->ghost->y()+75, doodle->pixmap().width(), 3);
    for (Platform* platform : platforms) {
        QRect platformRect(platform->x(), platform->y(), platform->pixmap().width(), platform->pixmap().height());
        if ((doodleRect.intersects(platformRect) || doodle_ghostRect.intersects(platformRect)) && Power < 0) {
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
void Gameplay::updateMoves() {
    doodle->updatePosition();
    for(Platform* platform:platforms) {
        platform->moveBy(0,Power);
    }
    score->add(Power);
    heightForSpawn+=Power;
    Power-=Gravity;
    if(heightForSpawn>= height()) {
        heightForSpawn = 0;
        emit newPlatformsNeeded();
    }
    for(int i = 0; i < platforms.size(); i++) {
        if(platforms[i]->y() > height()) {
            platforms[i]->hide();
            platforms.erase(platforms.begin()+i);
        }
    }
}

void Gameplay::newCreation() {
    spawnPlatformsReborn(platforms[platforms.size()-1]->y(), -height());
}

void Gameplay::makePause(){
    if(!stop) {
    if(!pause) {
        moveTimer->stop();
        pause = true;
        pauseMenuLabel->show();

    } else {
        moveTimer->start(16);
        pause = false;
        pauseMenuLabel->hide();
    }
    }
}

void Gameplay::makeStop() {
    for(int i = 0; i < platforms.size(); i++) {
        platforms[i]->hide();
    }
    platforms.clear();
    if(highScore < score->getscore()) {
        highScore = score->getscore();
        stopMenuLabel->setText("Your record: " + QString::number(highScore));
    }
    stop = true;
    stopMenuLabel->show();
    moveTimer->stop();
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
    case Qt::Key_R:
        if (stopMenuLabel->isVisible()) {
//            restartButton->click();
            stopMenuLabel->hide();
            stop = false;
            stopMenuLabel->setText("GAME OVER");
            platforms.clear();
            platforms.append(new Platform(256,216,scene, PlatType::Normal));
            doodle->setPos(256,128);
            doodle->ghost->setPos(-doodle->pixmap().width(), -doodle->pixmap().height());
            spawnPlatformsReborn(spawnPlatformsReborn(platforms[0]->y(),-height()));
            score->clear();
            Power = 20;
            score->add(63);
            moveTimer->start(16);
            heightForSpawn = 0;
        }
        break;
    case Qt::Key_Q:
        if (pauseMenuLabel->isVisible() || stopMenuLabel->isVisible()) {
            quitButton->click();
        }
        break;
    default:
        QGraphicsView::keyPressEvent(event); // Обработка других событий клавиатуры
    }
}

void Gameplay::wheelEvent(QWheelEvent *event)  {

}

int Gameplay::spawnPlatformsReborn(int startLow, int startHigh) {
    int jumpHeight = 180;
    int height_pos = startLow;
    int realWidth = width()-platforms[0]->pixmap().width();
    while(height_pos > startHigh)
    {
        PlatType type = PlatType::Normal;
        if(QRandomGenerator::global()->bounded(0,50) == 0) {
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
