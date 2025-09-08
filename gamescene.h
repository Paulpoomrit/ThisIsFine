#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "tilegraphicsitem.h"

#include <QGraphicsScene>
#include <tile.h>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject *parent);
    void initTileBoard(const std::vector<Tile*> &startingTileBoard,
                       const QSize &tileSize,
                       const int &column);
private:
    std::vector<TileGraphicsItem*> currentTileItemBoard;
public slots:
    void handleTileStateChanged(const int &tileIndex, TileState newState);
private slots:
    void handleTilePressed(const int &tileIndex);
signals:
    void tilePressed(const int &tileIndex);
};

#endif // GAMESCENE_H
