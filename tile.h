#ifndef TILE_H
#define TILE_H

#include <QObject>
#include "tilestates.h"

class tile : public QObject
{
    Q_OBJECT
public:
    explicit tile(QObject *parent = nullptr);
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
