#include "musicplayer.h"
#include <QDir>
#include <QRandomGenerator>
#include <QTextStream>
musicPlayer::musicPlayer() {
    QDir dir("../../assets/sound/music");
    filters = new QStringList;
    *filters << "*.mp3" << "*.MP3";
    QFileInfoList fileInfoList = dir.entryInfoList(*filters, QDir::Files);
    mp3FileNames = new QVector<QFileInfo>();
    QTextStream out(stdout);
    for (const QFileInfo &fileInfo : fileInfoList) {
        mp3FileNames->append(fileInfo.absoluteFilePath());
    }
    if(!mp3FileNames->isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(0,mp3FileNames->size());
        out << randomIndex;
        randomFileInfo = new QFileInfo;
        *randomFileInfo = mp3FileNames->at(randomIndex);
        setMedia(QUrl::fromLocalFile(randomFileInfo->absoluteFilePath()));
        play();
    }
}

QString musicPlayer::getFileName() {
    return randomFileInfo->fileName();
}



