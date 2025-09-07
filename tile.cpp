#include "tile.h"
#include "tilestates.h"

tile::tile(QObject *parent)
    : QObject{parent}
{}

void tile::ChangeHealth(int c)
{
    emit HealthChanged(c);
}

void tile::ChangeFire(int c)
{
    emit FireChanged(c);
}

void tile::ChangeState(TileState newState)
{
    // Emit a signal with both the new and old state
    emit StateChanged(newState, state);
    state = newState;
}
