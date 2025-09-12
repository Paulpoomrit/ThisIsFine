#include "gamescene.h"
#include "SpawnMode.h"
#include "flame.h"
#include "tilegraphicsitem.h"
#include "treegraphicsitem.h"
#include <QtCore/qsignalmapper.h>
#include <QGraphicsSceneWheelEvent>
#include <QRandomGenerator>
#include <qpushbutton.h>
#include <random>

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    currentTileItemBoard(),
    currentSpawnMode(SpawnMode::NONE),
    sfx(new SoundCue)
{
    QBrush backgroundBrush("#84c669");
    setBackgroundBrush(backgroundBrush);
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
    // QSignalMapper *mapper = new QSignalMapper(this);

    for (Tile* tile : startingTileBoard) {
        TileGraphicsItem *tileItem = new TileGraphicsItem(nullptr,
                                                          tile->GetState(),
                                                          tileSize,
                                                          sfx,
                                                          5,
                                                          tile,
                                                          currentTileItemBoard);

        currentTileItemBoard.push_back(tileItem);
        // mapper->setMapping(tileItem, currentTileItemBoard.size()-1);
        int tileIndex = currentTileItemBoard.size()-1;
        connect(tileItem, &TileGraphicsItem::pressed, this,[=](SpawnMode mode) {
            handleTilePressed(tileIndex, mode);
        });

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
    // connect (mapper, SIGNAL(mappedInt(int)), this, SLOT(handleTilePressed(int)));

    // -> Populate tree/flame only after all tiles are drawn
    // the Tree and Flame vectors are being spawned here
    // and pass to the TileGraphicsItem
    // this simply fixes the clipping problem we'd
    // otherwise encounter if we simply made them children of tile
    this->numAvgTreePerTile = numAvgTreePerTile;

    for (TileGraphicsItem *tile: currentTileItemBoard){
        std::vector<TreeGraphicsItem*> treeArray;
        std::vector<Flame*> flameArray;
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(numAvgTreePerTile, stdTreeDeviation);

        int numTree = 5;

        for (int i = 0; i < numTree; i++) {
            TreeGraphicsItem* treeItem = new TreeGraphicsItem();

            treeItem->setScale(1);
            int randomX = tile->pos().x() + QRandomGenerator::global()->bounded(tileSize.width());
            int randomY = tile->pos().y() + QRandomGenerator::global()->bounded(tileSize.height());
            treeItem->setPos(randomX, randomY);
            treeItem->setZValue(50);
            treeArray.push_back(treeItem);
            addItem(treeItem);

            // we're populating it here for
            // (a) performance and
            // (b) simple positioning
            Flame* flameItem = new Flame;
            flameItem->setScale(2);
            flameItem->setPos(randomX, randomY);
            flameItem->setZValue(60);
            flameItem->setVisible(false);
            flameArray.push_back(flameItem);
            addItem(flameItem);
        }
        tile->setTreeItems(treeArray);
        tile->setFlameItems(flameArray);

        // //test
        // tile->setCurrentTileState(TileState::DEAD);
    }

}

SpawnMode GameScene::getCurrentSpawnMode() const
{
    return currentSpawnMode;
}

void GameScene::setCurrentSpawnMode(SpawnMode newCurrentSpawnMode)
{
    if (newCurrentSpawnMode == currentSpawnMode) {
        return;
    }
    currentSpawnMode = newCurrentSpawnMode;
    for (TileGraphicsItem* tile : currentTileItemBoard) {
        tile->setCurrentSpawnMode(newCurrentSpawnMode);
    }
}

void GameScene::handleTileStateChanged(const int &tileIndex, TileState newState)
{
    const TileGraphicsItem* tile = currentTileItemBoard.at(tileIndex);
    if (tile->getCurrentTileState() == newState) {
        return;
    }
}

void GameScene::handleTilePressed(const int &tileIndex, SpawnMode mode)
{
    qDebug() << tileIndex;
    setCurrentSpawnMode(mode);
    emit tilePressed(tileIndex);
}

void GameScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    event->accept();
}
