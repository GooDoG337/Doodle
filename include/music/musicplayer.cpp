#include "musicplayer.h"
#include <QDir>
#include <QRandomGenerator>
#include <QTextStream>
#include <QDebug>
musicPlayer::musicPlayer() {
    QDir dir("../../assets/sound/music");
    filters = new QStringList;
    *filters << "*.mp3" << "*.MP3";
    QFileInfoList fileInfoList = dir.entryInfoList(*filters, QDir::Files);
    playlist = new QMediaPlaylist();

    for (const QFileInfo &fileInfo : fileInfoList) {
        playlist->addMedia(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    }
    if(!playlist->isEmpty())
    {
        playlist->shuffle();
        setPlaylist(playlist);
        play();
    } else {
        qWarning() << "No music found.";
    }
    connect(this, &musicPlayer::stateChanged, this, &musicPlayer::onPlaylistEnd);
}

QString musicPlayer::getFileName() {
    return currentMedia().canonicalUrl().fileName();
}
void musicPlayer::onPlaylistEnd() {
    if(state() == QMediaPlayer::StoppedState)
    {
        play();
    }
}

