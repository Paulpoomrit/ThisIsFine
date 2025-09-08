#include "retrobutton.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QEnterEvent>
#include <QGraphicsDropShadowEffect>

RetroButton::RetroButton(QWidget *parent) :
    QPushButton(parent),
    buttonClickedSFXArray({
        "qrc:/SFX/Content/SFX/airpods case closed 1.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 2.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 3.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 4.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 5.wav",
        "qrc:/SFX/Content/SFX/airpods case closed 6.wav"
    }),
    sfx(new QSoundEffect),
    shadow(new QGraphicsDropShadowEffect)
{
    shadow->setBlurRadius(6);
    shadow->setOffset(-2, -2);
    shadow->setColor(QColor("#1a1a1a"));
    setGraphicsEffect(shadow);
}

void RetroButton::playButtonClickedSound(const double& volume = 0.25)
{
    int randomSoundIndex = QRandomGenerator::global()->bounded(static_cast<int>(buttonClickedSFXArray.size()));
    sfx->setSource(QUrl(buttonClickedSFXArray.at(randomSoundIndex)));
    sfx->setVolume(volume);
    sfx->play();
}

void RetroButton::enterEvent(QEnterEvent *event)
{
    playButtonClickedSound();
    shadow->setBlurRadius(20);
    shadow->setOffset(2, 2);
    shadow->setColor(QColor("#ffffff"));
    Q_UNUSED(event);
}

void RetroButton::leaveEvent(QEvent *event)
{
    shadow->setBlurRadius(6);
    shadow->setOffset(-2, -2);
    shadow->setColor(QColor("#1a1a1a"));
    Q_UNUSED(event);
}
