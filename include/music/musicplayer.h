#pragma once
#include <QDir>
#include <QStringList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>
class musicPlayer:public QMediaPlayer
{
private:
    QStringList* filters;
    QFileInfo* randomFileInfo;
    QMediaPlaylist* playlist;
public:
    musicPlayer();
    QString getFileName();
public slots:
    void onPlaylistEnd();
};
