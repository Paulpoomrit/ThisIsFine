#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "configinfo.h"
#include "logicitems/tilelogic.h"
#include "managers/endgamestates.h"
#include "ui/gamewindow.h"
#include <QStackedWidget>
#include <variant>


class LevelManager : public QObject
{
    Q_OBJECT
public:
    LevelManager(GameWindow* gameWindow, GameScene* gameScene);

    static std::variant<Win, Lose> doLevel(ConfigInfo GameConfig);

    GameWindow *getGameWindow() const;
    void setGameWindow(GameWindow *newGameWindow);

    GameScene *getGameScene() const;
    void setGameScene(GameScene *newGameScene);

    void spawnTilesAndConnect();

private:
    GameWindow* gameWindow;
    GameScene* gameScene;

    std::vector<Tile*> tileBoard;
    std::vector<TileLogic*> tileLogicBoard;
    std::vector<TileGraphicsItem*>* tileGraphicsBoard;

};

#endif // LEVELMANAGER_H
