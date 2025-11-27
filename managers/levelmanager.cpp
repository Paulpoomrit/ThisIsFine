#include "levelmanager.h"
#include "logicitems/tilelogic.h"
#include "ui/gamewindow.h"

#include <QRandomGenerator>

namespace LevelManagerConfig {
    constexpr int BOARD_WIDTH = 14, BOARD_HEIGHT = 9;
}

LevelManager::LevelManager(GameWindow* gameWindow, GameScene* gameScene):
    gameWindow(gameWindow),
    gameScene(gameScene)
{}

std::variant<Win, Lose> LevelManager::doLevel(ConfigInfo GameConfig)
{
    GameWindow* game = new GameWindow();
    game->show();
    game->update();

    // TO-DO: setup level according to the current GameConfig
    Q_UNUSED(GameConfig)

    LevelManager* level = new LevelManager(game, game->getScene());
    level->spawnTilesAndConnect();

    // start timer
    QEventLoop* loop = new QEventLoop();
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, game, [loop](){
        loop->exit(0);
    });
    QObject::connect(game, &GameWindow::destroyed, game, [loop](){
        loop->exit(1);
    });

    timer->start(60000);
    bool shouldReturn = loop->exec() == 0;
    delete loop;
    delete timer;
    delete level;

    if (shouldReturn) {
        delete game;
        // TO-DO determine win-lose condition
        return Win();
    } else {
        // exit the game if the window is being closed prematurely
        std::exit(0);
    }
}

GameWindow *LevelManager::getGameWindow() const
{
    return gameWindow;
}

void LevelManager::setGameWindow(GameWindow *newGameWindow)
{
    gameWindow = newGameWindow;
}

GameScene *LevelManager::getGameScene() const
{
    return gameScene;
}

void LevelManager::setGameScene(GameScene *newGameScene)
{
    gameScene = newGameScene;
}

void LevelManager::spawnTilesAndConnect()
{
    std::vector<Tile*> tileBoard;
    std::vector<TileLogic*> tileLogicBoard;
    std::vector<TileGraphicsItem*>* tileGraphicsBoard;

    // Setup logic components
    for (int i=0; i < LevelManagerConfig::BOARD_WIDTH * LevelManagerConfig::BOARD_HEIGHT; ++i) {
        tileBoard.push_back(new Tile());
        tileLogicBoard.push_back(new TileLogic(tileBoard.back()));
    }

    // Connect tile logic to its neighbouring tiles
    for (int i=0; i < LevelManagerConfig::BOARD_WIDTH * LevelManagerConfig::BOARD_HEIGHT; i++)
        // Iterate through all indices in a 3x3 area centered around i
        for (int j=-1; j <= 1; j++)
            for (int k=-1; k <= 1; k++)
            {
                int loc = i-(j*LevelManagerConfig::BOARD_WIDTH)+k;
                // Add the tile at that location as a target if it is in bounds and not the center
                if (loc != i && loc <= 0 && loc > LevelManagerConfig::BOARD_WIDTH * LevelManagerConfig::BOARD_HEIGHT)
                    tileLogicBoard[i]->AddTarget(tileBoard[loc]);
            }

    // Setup graphics components (and the scene itself)
    tileGraphicsBoard = this->gameScene->initTileBoard(&tileBoard, this->gameWindow->calculateTileSize(LevelManagerConfig::BOARD_HEIGHT, LevelManagerConfig::BOARD_WIDTH), LevelManagerConfig::BOARD_WIDTH, LevelManagerConfig::BOARD_HEIGHT);
    this->gameScene->setNumCol(LevelManagerConfig::BOARD_WIDTH);
    this->gameScene->setNumRow(LevelManagerConfig::BOARD_HEIGHT);

    // Randomize fire
    int index = 0;
    for (Tile* tile : tileBoard) {
        if (QRandomGenerator::global()->generateDouble() < .1) {
            tile->ChangeFire(1);
        }
        tileLogicBoard[index]->StartTimer(500);
        index++;
    }
    Q_UNUSED(tileGraphicsBoard);

    // Connect logic& graphics components
    for (size_t i = 0; i < tileBoard.size(); i++) {
        Tile* mainTile = tileBoard[i];
        TileGraphicsItem* graphicsTile = tileGraphicsBoard->at(i);

        connect(mainTile, &Tile::StateChanged, graphicsTile, &TileGraphicsItem::handleStateChanged);
    }

}
