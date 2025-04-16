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
                Animate();
                break;
            case 16777236:
                anim->setEndValue(QPoint(doodle->x()+50, 0));
                doodle->setGeometry(doodle->x()+50,doodle->y(),120,75);
                break;
            case 16777234:
                anim->setEndValue(QPoint(doodle->x()-50, 0));
                doodle->setGeometry(doodle->x()-50,doodle->y(),120,75);
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
public:
    QLabel* doodle = new QLabel("Lada", this);
    QPropertyAnimation *anim = new QPropertyAnimation(doodle, "pos", this);
    Gameplay(QWidget* parent = nullptr);
    void Animate();
};
