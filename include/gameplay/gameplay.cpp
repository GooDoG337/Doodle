#include "gameplay.h"
void Gameplay::Animate() {
    anim->setDuration(2500);
    anim->setEndValue(QPoint(doodle->x(), 0));
    anim->setStartValue(QPoint(doodle->x(), height()-doodle->height()));
    anim->setEasingCurve(QEasingCurve::OutExpo);
    anim->start();
}
Gameplay::Gameplay(QWidget* parent):QWidget(parent){
    this->resize(512,512);
    bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Window, QBrush(*bkgnd));
    setPalette(*palette);
    doodle->setPixmap(QPixmap("../../assets/ladapriora.jpg"));
    doodle->setGeometry(0,height()-doodle->height()*2,120,75);
    //QObject::connect(&anim, SIGNAL(QPropertyAnimation::finished()),
    //                 &anim3, SLOT(ProperAnimate::FixupAnimate()));
    connect(anim, &ProperAnimation::finished, anim, &ProperAnimation::AutoReverse);
    //connect(anim, ProperAnimation::finished(), anim, ProperAnimation::AutoReverse());
    show();
}
