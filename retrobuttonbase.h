#ifndef RETROBUTTONBASE_H
#define RETROBUTTONBASE_H

#include <QPushButton>
#include <QSoundEffect>

class RetroButtonBase : public QPushButton
{
public:
    RetroButtonBase(QWidget *parent = nullptr);
private:
    std::vector <QString> buttonClickedSFXArray;
    QSoundEffect *sfx;
    void playButtonClickedSound(const double&);

protected:
    void enterEvent(QEnterEvent *event);
};

#endif // RETROBUTTONBASE_H
