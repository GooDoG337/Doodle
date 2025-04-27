#include <QHBoxLayout>
#include "volume.h"

Volume::Volume(QWidget *parent): QWidget(parent){
    auto *hbox = new QHBoxLayout(this);
    volume = new QSlider(Qt::Horizontal, this);
    hbox -> addWidget(volume);
    label = new QLabel("0", this);
    hbox -> addWidget(label);
    connect(volume , &QSlider::valueChanged, label, qOverload<int>(&QLabel::setNum));
}
