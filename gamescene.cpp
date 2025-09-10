#include "gamescene.h"
#include "tilegraphicsitem.h"
#include "treegraphicsitem.h"
#include <QtCore/qsignalmapper.h>
#include <QRandomGenerator>
#include <qpushbutton.h>
#include <random>

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    currentTileItemBoard(),
    sfx(new SoundCue)
{
}

void GameScene::initTileBoard(const std::vector<Tile*> &startingTileBoard,
                              const QSize &tileSize,
                              const int &column,
                              const int & numAvgTreePerTile)
{
    currentTileItemBoard.clear();
    QPoint currentPos(0,0);
    int xOffSet = tileSize.width();
    int yOffSet = tileSize.height();
    int columnCounter = 0;
    QSignalMapper *mapper = new QSignalMapper(this);

    for (Tile* tile : startingTileBoard) {
        TileGraphicsItem *tileItem = new TileGraphicsItem(nullptr, tile->GetState(), tileSize, sfx);

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

    // populate tree only after all tiles are drawn
    this->numAvgTreePerTile = numAvgTreePerTile;

    for (TileGraphicsItem *tile: currentTileItemBoard){
        std::vector<TreeGraphicsItem*> treeArray;
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(numAvgTreePerTile, stdTreeDeviation);
        // int numTree = distribution(generator);
        // qDebug () << numTree;

        int numTree = 5;

        for (int i = 0; i < numTree; i++) {
            TreeGraphicsItem* treeItem = new TreeGraphicsItem;

            // todo: adjust tree pos to be in the bounding rect
            treeItem->setScale(1);
            int randomX = tile->pos().x() + QRandomGenerator::global()->bounded(tileSize.width());
            int randomY = tile->pos().y() + QRandomGenerator::global()->bounded(tileSize.height());
            treeItem->setPos(randomX, randomY);
            treeItem->setZValue(50);
            treeArray.push_back(treeItem);
            addItem(treeItem);
        }
        tile->setTreeItems(treeArray);
    }

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
    emit tilePressed(tileIndex);
}
