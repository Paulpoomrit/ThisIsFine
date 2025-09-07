#include "retrobuttonbase.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QEnterEvent>

RetroButtonBase::RetroButtonBase(QWidget *parent) :
    QPushButton(parent),
    buttonClickedSFXArray({
        "qrc:/SFX/Content/SFX/airpods case closed 1.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 2.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 3.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 4.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 5.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 6.wav"
    }),
    sfx(new QSoundEffect)
{}

void RetroButtonBase::playButtonClickedSound(const double& volume = 0.25)
{
    int randomSoundIndex = QRandomGenerator::global()->bounded(static_cast<int>(buttonClickedSFXArray.size()));
    qDebug() << buttonClickedSFXArray.at(randomSoundIndex);
    sfx->setSource(QUrl(buttonClickedSFXArray.at(randomSoundIndex)));
    sfx->setVolume(volume);
    sfx->play();
}

void RetroButtonBase::enterEvent(QEnterEvent *event)
{
    playButtonClickedSound();
}
