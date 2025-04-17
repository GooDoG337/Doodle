#pragma once
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPropertyAnimation>
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
                    anim->setEndValue(QPoint(doodle->x()+25, 0));
                }
                break;
            case Qt::Key_Left:
                if(anim->state() == QPropertyAnimation::Stopped)
                {
                    doodle->setGeometry(doodle->x()-25,doodle->y(),120,75);
                } else {
                    anim->setEndValue(QPoint(doodle->x()-25, 0));
                }
                break;
        }
    }
public:
    QLabel* doodle = new QLabel("Lada", this);
    QPropertyAnimation *anim = new QPropertyAnimation(doodle, "pos", this);
    Gameplay(QWidget* parent = nullptr);
    void Animate();
};
