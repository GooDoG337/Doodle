#include "gameplay.h"
void Gameplay::Animate() {
    anim->setDuration(5000);
    anim->setStartValue(QPoint(doodle->x(), height()-doodle->height()));
    anim->setEndValue(QPoint(doodle->x(), 0));
    anim->setEasingCurve(QEasingCurve::OutExpo);
    anim->start();
}
Gameplay::Gameplay(QWidget* parent):QWidget(parent){
    this->resize(512,512);
    doodle->setPixmap(QPixmap("../../assets/ladapriora.jpg"));
    doodle->setGeometry(0,height()-doodle->height()*2,120,75);
    show();
}
