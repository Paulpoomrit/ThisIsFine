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
    void initTileBoard(std::vector<Tile>*);
};

#endif // GAMESCENE_H
