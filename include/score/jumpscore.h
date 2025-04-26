#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QWidget>

class Score : public QWidget {
    Q_OBJECT
public:
    Score(QWidget *parent = nullptr);
    void add(int i = 1);
    void updateRecord();
    ~Score();
public slots:
    void updateScoreLabel();
    void itsOver();
signals:
    void scoreChanged();
    void scoreZero();
private:
    QLabel *scoreLabel;
    int jumpscore;
    int record;
};
