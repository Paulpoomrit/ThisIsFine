#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include "tilestates.h"

class TileGraphicsItem : public QGraphicsPixmapItem
{
public:
    explicit TileGraphicsItem(QGraphicsItem *parent = nullptr, const TileState tileState = TileState::IDLE, const QSize &tileSize = QSize(50,50));
    TileState getCurrentTileState() const;
    void setCurrentTileState(TileState newCurrentTileState);

signals:
    void tileStateChanged(TileState newState);

private:
    TileState currentTileState;
};

#endif // TILEGRAPHICSITEM_H
