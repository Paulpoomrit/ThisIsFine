#ifndef RETROBUTTON_H
#define RETROBUTTON_H

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QSoundEffect>
#include <QWidget>
#include <QGraphicsEffect>

class RetroButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RetroButton(QWidget *parent = nullptr);

private:
    std::vector <QString> buttonClickedSFXArray;
    QSoundEffect *sfx;
    void playButtonClickedSound(const double& volume);

    QGraphicsDropShadowEffect *shadow;

protected:
    void enterEvent(QEnterEvent *event);

signals:
};

#endif // RETROBUTTON_H
