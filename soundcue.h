#ifndef SOUNDCUE_H
#define SOUNDCUE_H

#include <QSoundEffect>

enum SFX {
    PRESSED,
    HOVERED
};

class SoundCue : public QSoundEffect
{
public:
    explicit SoundCue(QObject *parent = nullptr);
    void playSFX(SFX type = SFX::PRESSED, const float &volume = 0.25);
private:
    const std::vector<QString> pressedSFXLocation;
    const std::vector<QString> hoveredSFXLocation;
    std::vector<QSoundEffect *>pressedSFX;
    std::vector<QSoundEffect *>hoveredSFX;
};

#endif // SOUNDCUE_H
