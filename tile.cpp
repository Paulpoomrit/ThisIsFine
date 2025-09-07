#include "tile.h"
#include "tilestates.h"

Tile::Tile(QObject *parent)
    : QObject{parent}
{}

TileState Tile::GetState() const
{
    return state;
}

void Tile::ChangeHealth(int c)
{
    emit HealthChanged(c);
}

void Tile::ChangeFire(int c)
{
    emit FireChanged(c);
}

void Tile::ChangeState(TileState newState)
{
    // Emit a signal with both the new and old state
    emit StateChanged(newState, state);
    state = newState;
}
