#pragma once
#include <QDir>
#include <QStringList>
#include <QMediaPlayer>
#include <QFileInfo>
class musicPlayer:public QMediaPlayer
{
private:
    QStringList* filters;
    QVector<QFileInfo>* mp3FileNames;
    QFileInfo* randomFileInfo;
    QVector<QFileInfo>* mp3BackupNames;
public:
    musicPlayer();
    QString getFileName();
};
