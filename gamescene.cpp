#include "gamescene.h"
#include "tilegraphicsitem.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    currentTileItemBoard()
{
}

void GameScene::initTileBoard(const std::vector<Tile*> &startingTileBoard,
                              const QSize &tileSize,
                              const int &column)
{
    currentTileItemBoard.clear();
    QPoint currentPos(0,0);
    int xOffSet = tileSize.width();
    int yOffSet = tileSize.height();
    int columnCounter = 0;

    for (Tile* tile : startingTileBoard) {
        TileGraphicsItem *tileItem = new TileGraphicsItem(nullptr, tile->GetState(), tileSize);
        currentTileItemBoard.push_back(tileItem);
        addItem(tileItem);
        tileItem->setPos(currentPos);

        columnCounter++;
        if (columnCounter == column) {
            currentPos.rx() = 0;
            columnCounter = 0;
            currentPos.ry() += yOffSet;
        } else {
            currentPos.rx() += xOffSet;
        }
    }
}
