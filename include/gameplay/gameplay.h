#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPropertyAnimation>
#include "../platform/platform.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
#include <QLabel>
#include <QList>
#include <QFileInfo>
#include <QMediaPlayer>
#include "../music/musicplayer.h"
class Gameplay : public QGraphicsView {
    Q_OBJECT
public:
    Gameplay(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void updateDoodlePosition();
    void onJumpFinished();
    void newCreation();
private:
    void checkCollison();
    QTimer* fpsTimer;
    QTimer* colisionTimer;
    bool higher = false;
    QGraphicsScene* scene;
    Doodle* doodle;
    QList<Platform*> platforms;
    int sceneWidth;
    int sceneHeight;
    Score* jumpscore;
    int highet = 0;
    int Power = 20;
    int Gravity = 1;
    void spawnPlatforms(int high, int num, bool stealth);
    int spawnPlatformsReborn(int startHigh = 0, int startLow = 0);
    void makePause();
    bool pause = false;
        QLabel* musicLabel;
    musicPlayer* musicplayer;
signals:
    void jumpFinished();
    void newParty();
};
