#include "truckgraphicsitem.h"

#include <QRandomGenerator>

TruckGraphicsItem::TruckGraphicsItem(QGraphicsItem *parent, const QPixmap &pixmap) :
    QGraphicsPixmapItem(parent)
{
    // std::vector<QString> sprites = {":/tiles/Content/Tiles/tile_0097.png",
    //                                 ":/tiles/Content/Tiles/tile_0115.png",
    //                                 ":/tiles/Content/Tiles/tile_0133.png",
    //                                 ":/tiles/Content/Tiles/tile_0151.png",
    //                                 ":/tiles/Content/Tiles/tile_0169.png"};
    // int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(sprites.size()));
    // QPixmap pixmap(sprites.at(randomIndex));
    setPixmap(pixmap);
}
