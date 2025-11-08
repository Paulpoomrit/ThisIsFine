#ifndef TILE_H
#define TILE_H

#include <QObject>
#include "tilestates.h"

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr);
    TileState GetState() const;
    void ChangeHealth(int);
    void ChangeFire(int);
    void ChangeState(TileState);

signals:
    void HealthChanged(int);
    void FireChanged(int);
    void StateChanged(TileState, TileState);

private:
    TileState state;
signals:
};

#endif // TILE_H
