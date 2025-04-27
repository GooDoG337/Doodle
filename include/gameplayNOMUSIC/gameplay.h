#pragma once
#include "../platform/platform.h"
#include "../doodle/doodle.h"
#include "../score/jumpscore.h"
<<<<<<< HEAD
#include "../volume/volume.h"
=======
#include <QLabel>
#include <QList>
#include <QFileInfo>
#include <QPushButton>
>>>>>>> d6684096e9cd095e7114765e85099bca3d1a4eb3
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
    int heightForSpawn = 0;
    int Power = 20;
    int Gravity = 1;
    int spawnPlatformsReborn(int startHigh = 0, int startLow = 0);
    void makePause();   QLabel* pauseMenuLabel;
    void makeStop();    QLabel* stopMenuLabel;
    bool pause = false;
<<<<<<< HEAD
=======
    QGraphicsPixmapItem* doodle_clone;

    QPushButton *restartButton;
    QPushButton *quitButton;


>>>>>>> d6684096e9cd095e7114765e85099bca3d1a4eb3
signals:
    void newPlatformsNeeded();
};
