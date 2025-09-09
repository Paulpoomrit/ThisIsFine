#ifndef SOUNDCUE_H
#define SOUNDCUE_H

#include <QSoundEffect>

enum SFX {
    PRESSED,
    HOVERED,
    DIRT
};

class SoundCue : public QObject
{
public:
    explicit SoundCue(QObject *parent = nullptr);
    void playSFX(SFX type = SFX::PRESSED, const float &volume = 0.25);
private:
    const std::vector<QString> pressedSFXLocation;
    const std::vector<QString> hoveredSFXLocation;
    const std::vector<QString> dirtSFXLocation;
    std::vector<QSoundEffect *>pressedSFX;
    std::vector<QSoundEffect *>hoveredSFX;
    std::vector<QSoundEffect *>dirtSFX;
};

#endif // SOUNDCUE_H
