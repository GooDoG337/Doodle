#pragma once
#include <QWidget>
#include <QSlider>
#include <QLabel>

class Volume: public QWidget{
    Q_OBJECT
public:
    Volume(QWidget* parent = nullptr);
private:
    QSlider* volume;
    QLabel* label;
};
