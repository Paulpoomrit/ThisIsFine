#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "SpawnMode.h"
#include "soundcue.h"
#include "tilegraphicsitem.h"

#include <QGraphicsScene>
#include "tile.h"


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject *parent);
    void initTileBoard(const std::vector<Tile*> &startingTileBoard = std::vector<Tile*>(),
                       const QSize &tileSize = QSize(100,100),
                       const int &column = 5,
                       const int & numAvgTreePerTile = 5);
    SpawnMode getCurrentSpawnMode() const;
    void setCurrentSpawnMode(SpawnMode newCurrentSpawnMode);

private:
    std::vector<TileGraphicsItem*> currentTileItemBoard;

    int numAvgTreePerTile;
    int stdTreeDeviation = 5;

    SpawnMode currentSpawnMode;

    SoundCue* sfx;
public slots:
    void handleTileStateChanged(const int &tileIndex, TileState newState);
private slots:
    void handleTilePressed(const int &tileIndex, SpawnMode);
signals:
    void tilePressed(const int &tileIndex);
};

#endif // GAMESCENE_H
