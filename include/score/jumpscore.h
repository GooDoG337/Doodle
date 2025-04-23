#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QWidget>

class Score : public QWidget {
    Q_OBJECT
public:
    Score(QWidget *parent = nullptr);
    void add(int i = 1);
    ~Score();
public slots:
    void updateScoreLabel();
signals:
    void scoreChanged();
private:
    QLabel *scoreLabel;
    int jumpscore;
};
