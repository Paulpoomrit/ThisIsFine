#include "tilegraphicsitem.h"

#include <qrandom.h>

TileGraphicsItem::TileGraphicsItem(QGraphicsItem *parent, const TileState tileState, const QSize &tileSize) :
    QGraphicsPixmapItem(parent),
    currentTileState(tileState)
{
    std::vector<QString> tileSprites = {":/tiles/Content/Tiles/tile_0000.png",
                                        ":/tiles/Content/Tiles/tile_0001.png",
                                        ":/tiles/Content/Tiles/tile_0002.png"};
    int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(tileSprites.size()));
    QPixmap pixmap(tileSprites.at(randomIndex));
    pixmap = pixmap.scaled(tileSize.width(), tileSize.height());
    setPixmap(pixmap);
}

TileState TileGraphicsItem::getCurrentTileState() const
{
    return currentTileState;
}

void TileGraphicsItem::setCurrentTileState(TileState newCurrentTileState)
{
    currentTileState = newCurrentTileState;
}
