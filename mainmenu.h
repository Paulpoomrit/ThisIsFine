#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include "gamemode.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void gameStarted(GameMode gameModeSelected);

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
