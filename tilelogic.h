#ifndef TILELOGIC_H
#define TILELOGIC_H

#include <QObject>
#include <QTimer>
#include "tile.h"
#include "tilestates.h"

class TileLogic : public QObject
{
    Q_OBJECT
public:
    TileLogic(Tile*, int = 3, int = 1, int = 10, double = 0.01, double = 0.04);
    void AddTarget(Tile*);
    void StartTimer(int);

private slots:
    void UpdateTick();
    void ChangeFireIntensity(int);
    void ChangeHealth(int);
    void ChangeFireState(TileState, TileState);

private:
    Tile* mainTile;
    std::vector<Tile*> spreadableTargets;
    int health;
    int fireIntensity;
    int maxFireIntensity;
    int ticksUntilDamage;
    int ticksForDamage;
    double combustChance;
    double spreadToChance;
    TileState state;
    QTimer* tick;
};

#endif // TILELOGIC_H
