#pragma once
#include "../platform/platform.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
#include "../volume/volume.h"
#include "../music/musicplayer.h"
#include "../background/background.h"
#include <QPushButton>
#include <QSlider>
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
    void newMediaPlaying();
private:
    void wheelEvent(QWheelEvent *event) override;
    void checkCollison();
    QTimer* moveTimer;
    QGraphicsScene* scene;
    Doodle* doodle;
    QList<Platform*> platforms;
    Background* bckgrnd;
    QSlider* volume;
    void restartGame();
    int sceneWidth = 512;
    int sceneHeight = 512;
    Score* score;
    int highScore = 0;
    int heightForSpawn = 0;
    int Power = 20;
    int Gravity = 1;
    int spawnPlatformsReborn(int startHigh = 0, int startLow = 0);
    void makePause(); QLabel* pauseMenuLabel;
    void makeStop();  QLabel* stopMenuLabel;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QPushButton *resumeButton;
    QLabel* musicLabel;
    musicPlayer* mplayer;
    bool pause = false;
    bool stop = false;
signals:
    void newPlatformsNeeded();
};
