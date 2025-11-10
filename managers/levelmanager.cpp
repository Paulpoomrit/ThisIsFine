#include "levelmanager.h"
#include "logicitems/tilelogic.h"
#include "ui/gamewindow.h"

#include <QRandomGenerator>

LevelManager::LevelManager(GameWindow* gameWindow, GameScene* gameScene):
    gameWindow(gameWindow),
    gameScene(gameScene)
{}

std::variant<Win, Lose> LevelManager::doLevel(ConfigInfo GameConfig, QStackedWidget* parent)
{
    GameWindow* game = new GameWindow();
    parent->addWidget(game);
    parent->setCurrentWidget(game);
    parent->show();
    LevelManager* level = new LevelManager(game, game->getScene());

    std::vector<Tile*> tileBoard;
    std::vector<TileLogic*> tileLogicBoard;

    int boardWidth = 14, boardHeight = 9;
    for (int i=0; i < boardWidth*boardHeight; ++i) {
        tileBoard.push_back(new Tile());
        tileLogicBoard.push_back(new TileLogic(tileBoard.back()));
    }
    // Connect tile logic to its neighbouring tiles
    for (int i=0; i < boardWidth*boardHeight; i++)
        // Iterate through all indices in a 3x3 area centered around i
        for (int j=-1; j <= 1; j++)
            for (int k=-1; k <= 1; k++)
            {
                int loc = i-(j*boardWidth)+k;
                // Add the tile at that location as a target if it is in bounds and not the center
                if (loc != i && loc <= 0 && loc > boardWidth*boardHeight)
                    tileLogicBoard[i]->AddTarget(tileBoard[loc]);
            }

    game->getScene()->initTileBoard(&tileBoard, game->calculateTileSize(boardHeight,boardWidth), boardWidth, boardHeight);
    game->getScene()->setNumCol(boardWidth);
    game->getScene()->setNumRow(boardHeight);

    // randomize fire
    int index = 0;
    for (Tile* tile : tileBoard) {
        if (QRandomGenerator::global()->generateDouble() < .1) {
            tile->ChangeFire(1);
        }
        tileLogicBoard[index]->StartTimer(500);
        index++;
    }

    // start timer
    QEventLoop loop;
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, parent, [&loop](){
        loop.quit();
    });
    timer->start(60000);
    loop.exec();
    parent->removeWidget(game);
    return Win();
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
