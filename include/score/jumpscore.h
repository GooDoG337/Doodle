#pragma once
#include <QLabel>
#include <QWidget>

class Score : public QWidget {
    Q_OBJECT
public:
    Score(QWidget *parent = nullptr);
    void add(int i);
    void updateRecord();
    void clear();
    ~Score();
    int getscore();
public slots:
    void updateScoreLabel();
    void itsOver();
signals:
    void scoreChanged();
    void scoreZero();
private:
    QLabel *scoreLabel;
    int jumpscore = 0;
    int record = 0;
};
