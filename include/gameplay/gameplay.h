#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPropertyAnimation>
#include "../platform/platform.h"
#include "../doodle/doodle.h"
#include <QList>
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
private:
    void checkCollison();
    QTimer* fpsTimer;
    bool higher = false;
    QGraphicsScene* scene;
    Doodle* doodle;
    QList<Platform*> platforms;
    int sceneWidth;
    int sceneHeight;
    void spawnPlatforms();
signals:
    void jumpFinished();
};
