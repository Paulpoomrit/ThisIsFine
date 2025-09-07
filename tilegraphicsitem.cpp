#include "tilegraphicsitem.h"

TileGraphicsItem::TileGraphicsItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/tiles/Content/Tiles/tile_0000.png");
    setPixmap(pixmap);
}
