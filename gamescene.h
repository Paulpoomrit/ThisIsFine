#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <tile.h>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject *parent);
private:
    std::vector<Tile*> currentTileBoard;
    void initTileBoard(std::vector<Tile*> startingTileBoard);
    void updateTileBoard(std::vector<Tile*> NewTileBoard);
};

#endif // GAMESCENE_H
