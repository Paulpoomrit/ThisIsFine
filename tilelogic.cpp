#include "tilelogic.h"

#include <QTimer>
#include <QRandomGenerator>

#include "tile.h"
#include "tilestates.h"

TileLogic::TileLogic(
    Tile* mainTile,
    int health,
    int maxFireIntensity,
    int ticksForDamage,
    double combustChance,
    double spreadChance
)
    : mainTile(mainTile)
    , health(health)
    , fireIntensity(0)
    , maxFireIntensity(maxFireIntensity)
    , ticksUntilDamage(ticksForDamage)
    , ticksForDamage(ticksForDamage)
    , combustChance(combustChance)
    , spreadToChance(spreadChance)
    , state(IDLE)
{
    // Connect tile
    QObject::connect(mainTile, &Tile::FireChanged, this, &TileLogic::ChangeFireIntensity);
    QObject::connect(mainTile, &Tile::StateChanged, this, &TileLogic::ChangeFireState);
    QObject::connect(mainTile, &Tile::HealthChanged, this, &TileLogic::ChangeHealth);

    // Connect tick
    tick = new QTimer(this);
    QObject::connect(tick, &QTimer::timeout, this, &TileLogic::UpdateTick);
}

void TileLogic::AddTarget(Tile* newTile)
{
    spreadableTargets.push_back(newTile);
}

void TileLogic::StartTimer(int tickInterval)
{
    tick->start(tickInterval);
}

void TileLogic::UpdateTick()
{
    // Burning behaviour
    if (state == BURNING)
    {
        // Tick towards damage
        ticksUntilDamage--;
        if (ticksUntilDamage <= 0)
        {
            mainTile->ChangeHealth(-1);
            ticksUntilDamage = ticksForDamage;
        }

        // Attempt to spread fire to targets
        for (int i=0; i < spreadableTargets.size(); i++)
            if (spreadToChance > QRandomGenerator::global()->generateDouble())
                spreadableTargets[i]->ChangeFire(1);
    }
    // Idle behaviour
    else if (state == IDLE)
    {
        // Attempt to spontaneously combust
        if (combustChance > QRandomGenerator::global()->generateDouble())
            mainTile->ChangeFire(1);
    }
}

void TileLogic::ChangeFireIntensity(int change)
{
    // Change fire intensity, clamped between 0 and max
    fireIntensity = qBound(0, fireIntensity+change, maxFireIntensity);
    // Update the tile's current state
    if (state == DEAD)
    {
        if (fireIntensity == 0)
            mainTile->ChangeState(IDLE);
        else
            mainTile->ChangeState(BURNING);
    }
}

void TileLogic::ChangeHealth(int change)
{
    health = qMax(0, health+change);
    if (health == 0)
        mainTile->ChangeState(DEAD);
}

void TileLogic::ChangeFireState(TileState newState, TileState)
{
    state = newState;
}
