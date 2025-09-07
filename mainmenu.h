#ifndef MAINMENU_H
#define MAINMENU_H

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
    void gameStarted(GameMode);

private:
    Ui::MainMenu *ui;
    void startGame(GameMode);
    void exitGame();
};

#endif // MAINMENU_H
