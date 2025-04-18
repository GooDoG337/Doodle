#pragma once
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTextStream>
#include <iostream>
class ProperAnimation:public QPropertyAnimation {
    Q_OBJECT
public:
    ProperAnimation(QObject* some, QByteArray text, QWidget* parent):QPropertyAnimation(some,text,parent) {}
public slots:
    void AutoReverse() {
        if(direction() == QAbstractAnimation::Forward)
        {
            setDirection(QAbstractAnimation::Backward);
        } else {
            setDirection(QAbstractAnimation::Forward);
        }
        start(QAbstractAnimation::KeepWhenStopped);
    }
};
/*class ProperAnimate: QObject {
    Q_OBJECT
public:
    ProperAnimate() {}
public slots:
    void FixupAnimate(QPropertyAnimation* animate) {
        if(animate->direction() == QAbstractAnimation::Forward)
        {
            animate->setDirection(QAbstractAnimation::Backward);
        } else {
            animate->setDirection(QAbstractAnimation::Forward);
        }
        animate->start(QAbstractAnimation::DeleteWhenStopped);
    }
};*/

class Gameplay: QWidget {
protected:
    //Обработка КНОПОК КЛАВИАТУРЫ
    void keyPressEvent(QKeyEvent *event) override {
        switch(event->key())
        {
            case 16777220:
            case Qt::Key_Enter: //На моём компе не работает
                Animate();
                break;
            case Qt::Key_Right:
                if(anim->state() == QPropertyAnimation::Stopped)
                {
                    doodle->setGeometry(doodle->x()+25,doodle->y(),120,75);
                } else {
                    anim->setStartValue(QPoint(doodle->x()+25, height()-doodle->height()));
                    anim->setEndValue(QPoint(doodle->x()+25, 0));
                }
                break;
            case Qt::Key_Left:
                if(anim->state() == QPropertyAnimation::Stopped)
                {
                    doodle->setGeometry(doodle->x()-25,doodle->y(),120,75);
                } else {
                    anim->setStartValue(QPoint(doodle->x()-25, height()-doodle->height()));
                    anim->setEndValue(QPoint(doodle->x()-25, 0));
                }
                break;
        }
    }
public:
    QLabel* doodle = new QLabel("doodle", this);
    QPixmap* bkgnd = new QPixmap("../../assets/background.png");
    ProperAnimation *anim = new ProperAnimation(doodle, "pos", this);
    Gameplay(QWidget* parent = nullptr);
    void Animate();
};
