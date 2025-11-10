#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "configinfo.h"
#include "managers/endgamestates.h"
#include "ui/gamewindow.h"
#include <QStackedWidget>
#include <variant>


class LevelManager
{
public:
    LevelManager(GameWindow* gameWindow, GameScene* gameScene);
    static std::variant<Win, Lose> doLevel(ConfigInfo GameConfig, QStackedWidget* parent);

    GameWindow *getGameWindow() const;
    void setGameWindow(GameWindow *newGameWindow);

    GameScene *getGameScene() const;
    void setGameScene(GameScene *newGameScene);

private:
    GameWindow* gameWindow;
    GameScene* gameScene;

};

#endif // LEVELMANAGER_H
