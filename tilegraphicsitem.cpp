#include "tilegraphicsitem.h"

#include <QPainter>
#include <QPixmap>
#include <qrandom.h>

TileGraphicsItem::TileGraphicsItem(QGraphicsObject *parent, const TileState tileState, const QSize &tileSize) :
    QGraphicsObject(parent),
    currentTileState(tileState),
    tileSize(tileSize),
    tileSprite(new QPixmap)
{
    std::vector<QString> tileSprites = {":/tiles/Content/Tiles/tile_0000.png",
                                        ":/tiles/Content/Tiles/tile_0001.png",
                                        ":/tiles/Content/Tiles/tile_0002.png"};
    int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(tileSprites.size()));
    QPixmap pixmap(tileSprites.at(randomIndex));
    *tileSprite = pixmap.scaled(tileSize.width(), tileSize.height());
}

TileState TileGraphicsItem::getCurrentTileState() const
{
    return currentTileState;
}

void TileGraphicsItem::setCurrentTileState(TileState newCurrentTileState)
{
    if (currentTileState == newCurrentTileState) {
        return;
    }
    currentTileState = newCurrentTileState;
    // todo: set graphics
    // todo: play sound
}


QRectF TileGraphicsItem::boundingRect() const
{
    return QRectF(0,0,tileSize.width(), tileSize.height());
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(QPoint(0,0), *tileSprite);
}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit pressed();
}
