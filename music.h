#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QSoundEffect>

class music
{
public:
    music();
    ~music();
    QMediaPlayer* _player;
    QAudioOutput* _audioOutput;
};

#endif // MUSIC_H
