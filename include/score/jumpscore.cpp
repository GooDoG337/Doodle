#include "jumpscore.h"

Score::Score(QWidget* parent): QWidget(parent){
    scoreLabel = new QLabel(this);
    scoreLabel->setText("Score: 0");
    scoreLabel->setStyleSheet("font-size: 16px; color: white; background-color: rgba(0, 0, 0, 150); padding: 1px;");
    scoreLabel->setGeometry(10, 10, 150, 40);  // позиция и размер на экране
    scoreLabel->show();
    connect(this, &Score::scoreChanged, this, &Score::updateScoreLabel);
    connect(this, &Score::scoreZero, this, &Score::itsOver);
    setStyleSheet("background-color: #222;");
}

Score::~Score() {}

void Score::add(int i) {
    jumpscore+=i;
    if(i == 0) {
        updateRecord();
    }
    if(jumpscore > 0)
    {
        emit scoreChanged();
    } else {
        emit scoreZero();
    }

}
void Score::updateScoreLabel(){
    scoreLabel->setText("Score: " + QString::number(jumpscore));
}

void Score::itsOver() {
    scoreLabel->setStyleSheet("font-size: 12px; color: white; background-color: rgba(0, 0, 0, 150); padding: 1px;");
    scoreLabel->setText("Your record: " + QString::number(record));
}
void Score::updateRecord() {
    record = jumpscore;
}
void Score::clear() {
    scoreLabel->setStyleSheet("font-size: 24px; color: white; background-color: rgba(0, 0, 0, 150); padding: 1px;");
    record = 0;
    jumpscore = 0;
}
int Score::getscore() {
    return record;
}
