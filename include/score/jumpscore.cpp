#include "jumpscore.h"


jumpScore::jumpScore(QWidget* parent): QWidget(parent){
    scoreLabel = new QLabel(this);
    scoreLabel->setText("Score: 0");
    scoreLabel->setStyleSheet("font-size: 24px; color: white; background-color: rgba(0, 0, 0, 150); padding: 5px;");
    scoreLabel->setGeometry(10, 10, 150, 40);  // позиция и размер на экране
    scoreLabel->show();

    setFixedSize(400, 600);  // Размер окна игры
    setStyleSheet("background-color: #222;");
}

jumpScore::~jumpScore() {}


void jumpScore::updateScoreLabel(){
    scoreLabel->setText("Score: " + QString::number(score));
}
