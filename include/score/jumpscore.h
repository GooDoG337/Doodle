#pragma once
#include "../gameplay/gameplay.h"
#include <QMainWindow>
#include <QLabel>
#include <QWidget>

class jumpScore : public QWidget {
    Q_OBJECT

public:
    jumpScore(QWidget *parent = nullptr);
    ~jumpScore();

private:
    QLabel *scoreLabel;
    int score;

    void updateScoreLabel();
};
