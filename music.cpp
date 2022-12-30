#include "music.h"

music::music()
{
     _player = new QMediaPlayer;
     _audioOutput = new QAudioOutput;
     _player->setAudioOutput(_audioOutput);
     _player->setSource(QUrl("qrc:/1.mp3"));
     _audioOutput->setVolume(1);
     _player->play();
     _player->setLoops(9999);

}

music::~music()
{
    delete _player;
    delete _audioOutput;
}
