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
    void initTileBoard(std::vector<Tile*>* startingTileBoard = new std::vector<Tile*>(),
                       const QSize &tileSize = QSize(100,100),
                       const int &column = 5,
                       const int & numAvgTreePerTile = 5);
    SpawnMode getCurrentSpawnMode() const;
    void setCurrentSpawnMode(SpawnMode newCurrentSpawnMode);

    std::vector<Tile *>* getBaseTileBoard() const;
    void setBaseTileBoard(std::vector<Tile *> *newBaseTileBoard);

    int getNumRow() const;
    void setNumRow(int newNumRow);

    int getNumCol() const;
    void setNumCol(int newNumCol);

private:
    std::vector<TileGraphicsItem*> currentTileItemBoard;
    std::vector<Tile*>* baseTileBoard;

    std::vector<Tile*>* paulSucksTileBoard;

    int numAvgTreePerTile;
    int stdTreeDeviation = 5;

    SpawnMode currentSpawnMode;

    SoundCue* sfx;

    int numRow;
    int numCol;

public slots:
    void handleTileStateChanged(const int &tileIndex, TileState newState);
private slots:
    void handleTilePressed(const int &tileIndex, SpawnMode);
signals:
    void tilePressed(const int &tileIndex);

    // QGraphicsScene interface
protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event);
};

#endif // GAMESCENE_H
