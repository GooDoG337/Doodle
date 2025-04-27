#pragma once
#include "../platform/platform.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
#include "../volume/volume.h"
#include "../background/background.h"
#include <QLabel>
#include <QList>
#include <QFileInfo>
#include <QPushButton>
class Gameplay : public QGraphicsView {
    Q_OBJECT
public:
    Gameplay(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void updateMoves();
    void newCreation();
private:
    void wheelEvent(QWheelEvent *event) override;
    void checkCollison();
    QTimer* moveTimer;
    QGraphicsScene* scene;
    Doodle* doodle;
    QList<Platform*> platforms;

    int sceneWidth = 512;
    int sceneHeight = 512;
    Score* score;
    Background* bckgrnd;
    int heightForSpawn = 0;
    int Power = 0;
    int Gravity = 1;
    int spawnPlatformsReborn(int startHigh = 0, int startLow = 0);
    void makePause();   QLabel* pauseMenuLabel;
    void makeStop();    QLabel* stopMenuLabel;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QLabel* musicLabel;
    bool pause = false;
    bool stop = false;

signals:
    void newPlatformsNeeded();
};
