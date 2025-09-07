#include "gamescene.h"
#include "tilegraphicsitem.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void GameScene::initTileBoard(std::vector<Tile*> startingTileBoard)
{
    currentTileBoard = startingTileBoard;
}
