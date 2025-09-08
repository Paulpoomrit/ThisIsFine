#include "soundcue.h"

#include <qrandom.h>

SoundCue::SoundCue(QObject *parent)
    : QSoundEffect{parent},
    pressedSFX({
        "qrc:/SFX/Content/SFX/button pressed 1.wav",
        "qrc:/SFX/Content/SFX/button pressed 2.wav",
        "qrc:/SFX/Content/SFX/button pressed 3.wav",
        "qrc:/SFX/Content/SFX/button pressed 4.wav",
        "qrc:/SFX/Content/SFX/button pressed 5.wav",
        "qrc:/SFX/Content/SFX/button pressed 6.wav",
        "qrc:/SFX/Content/SFX/button pressed 7.wav",
        "qrc:/SFX/Content/SFX/button pressed 8.wav",
        "qrc:/SFX/Content/SFX/button pressed 9.wav",
        "qrc:/SFX/Content/SFX/button pressed 10.wav",
        "qrc:/SFX/Content/SFX/button pressed 11.wav",
        "qrc:/SFX/Content/SFX/button pressed 12.wav",
        "qrc:/SFX/Content/SFX/button pressed 13.wav",
        "qrc:/SFX/Content/SFX/button pressed 14.wav",
        "qrc:/SFX/Content/SFX/button pressed 15.wav",
    }),
    hoveredSFX({
       "qrc:/SFX/Content/SFX/airpods case closed 1.wav",
       "qrc:/SFX/Content/SFX/airpods case closed 2.wav",
       "qrc:/SFX/Content/SFX/airpods case closed 3.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 4.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 5.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 6.wav"
    })
{}

void SoundCue::playSFX(SFX type, const float &volume)
{
    std::vector<QString> sfxSource;
    switch(type) {
    case SFX::HOVERED:
        sfxSource = hoveredSFX;
        break;
    case SFX::PRESSED:
        sfxSource = pressedSFX;
        break;
    }
    int randomSoundIndex = QRandomGenerator::global()->bounded(static_cast<int>(sfxSource.size()));
    setSource(QUrl(sfxSource.at(randomSoundIndex)));
    setVolume(volume);
    play();

}
