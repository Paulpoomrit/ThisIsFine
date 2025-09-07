#include "gamescene.h"
#include "tilegraphicsitem.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    TileGraphicsItem *tile = new TileGraphicsItem();
    addItem(tile);
}
