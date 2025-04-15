#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <iostream>
class MyButton:public QWidget {
private:
    QPushButton *quitBtn = new QPushButton(QString("Release HL:EP3"), this);
    int height_pos;
    int width_pos;
    int height_size = 64;
    int width_size = 128;
public:
    MyButton(QWidget *parrent = 0);
    void Animate();
};
MyButton::MyButton(QWidget *parrent):QWidget(parrent){
    height_pos = (height()-height_size)/2;
    width_pos = (width()-width_size)/2;
    quitBtn->setGeometry(width_pos,height_pos,width_size,height_size);
    connect(quitBtn, &QPushButton::clicked, this, &MyButton::Animate);
}
void MyButton::Animate(){
    if(height_pos > 9) {
        height_pos-=10;
        quitBtn->setGeometry(width_pos,height_pos,width_size,height_size);
    }
    else {
        height_pos = 0;
        quitBtn->setGeometry(width_pos,height_pos,width_size,height_size);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyButton window;
    window.show();
    return a.exec();
}

//Фигня, а не код, единственное, что тут есть - подьём кнопки.
