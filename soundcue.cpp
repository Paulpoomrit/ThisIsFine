#include "soundcue.h"

#include <QtCore/qstringliteral.h>
#include <qrandom.h>

SoundCue::SoundCue(QObject *parent)
    : QObject{parent},
    pressedSFXLocation({
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 1.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 2.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 3.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 4.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 5.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 6.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 7.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 8.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 9.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 10.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 11.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 12.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 13.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 14.wav"),
        QStringLiteral("qrc:/SFX/Content/SFX/button pressed 15.wav"),
    }),
    hoveredSFXLocation({
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 1.wav"),
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 2.wav"),
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 3.wav"),
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 4.wav"),
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 5.wav"),
       QStringLiteral("qrc:/SFX/Content/SFX/airpods case closed 6.wav"),
    })
{
    for (const auto &path : pressedSFXLocation) {
        QSoundEffect *sfx = new QSoundEffect();
        sfx->setSource(path);
        pressedSFX.push_back(sfx);
    }
    for (const auto &path : hoveredSFXLocation) {
        QSoundEffect *sfx = new QSoundEffect();
        sfx->setSource(path);
        hoveredSFX.push_back(sfx);
    }
}

void SoundCue::playSFX(SFX type, const float &volume)
{
    std::vector<QSoundEffect *> sfxSource;
    switch(type) {
    case SFX::HOVERED:
        sfxSource = hoveredSFX;
        break;
    case SFX::PRESSED:
        sfxSource = pressedSFX;
        break;
    }
    int randomSoundIndex = QRandomGenerator::global()->bounded(static_cast<int>(sfxSource.size()));
    QSoundEffect *effect = sfxSource.at(randomSoundIndex);
    effect->setVolume(volume);
    sfxSource.at(randomSoundIndex)->play();
}
