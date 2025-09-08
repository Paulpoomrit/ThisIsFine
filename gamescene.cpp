#include "gamescene.h"
#include "tilegraphicsitem.h"
#include <QtCore/qsignalmapper.h>
#include <qpushbutton.h>

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
    QSignalMapper *mapper = new QSignalMapper(this);

    for (Tile* tile : startingTileBoard) {
        TileGraphicsItem *tileItem = new TileGraphicsItem(nullptr, tile->GetState(), tileSize);

        currentTileItemBoard.push_back(tileItem);
        mapper->setMapping(tileItem, currentTileItemBoard.size()-1);
        connect(tileItem, SIGNAL(pressed()), mapper, SLOT(map()));

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
    connect (mapper, SIGNAL(mappedInt(int)), this, SLOT(handleTilePressed(int)));
}

void GameScene::handleTileStateChanged(const int &tileIndex, TileState newState)
{
    const TileGraphicsItem* tile = currentTileItemBoard.at(tileIndex);
    if (tile->getCurrentTileState() == newState) {
        return;
    }
}

void GameScene::handleTilePressed(const int &tileIndex)
{
    qDebug() << tileIndex;
    currentTileItemBoard.at(tileIndex);
    emit tilePressed(tileIndex);
}
