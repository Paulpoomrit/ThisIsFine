#include "truckgraphicsitem.h"

#include <QRandomGenerator>

TruckGraphicsItem::TruckGraphicsItem(QGraphicsItem *parent, const QPixmap &pixmap, const std::vector<TileGraphicsItem *> parentTileBoard) :
    QObject(),
    QGraphicsPixmapItem(parent),
    parentTileBoard(parentTileBoard),
    moveAnimation(new QPropertyAnimation(this))
{
}

QPoint TruckGraphicsItem::getTruckPos() const
{
    return truckPos;
}

void TruckGraphicsItem::setTruckPos(QPoint newTruckPos)
{
    truckPos = newTruckPos;

    setPos(newTruckPos);
    emit truckPosChanged(newTruckPos);
}

void TruckGraphicsItem::moveTo(int startIndex, int stopIndex, int travelTime)
{
    // Get pos for the starting tile
    QPointF startPos = parentTileBoard[startIndex]->pos();
    QPointF endPos = parentTileBoard[stopIndex]->pos();

    moveAnimation->setTargetObject(this);
    moveAnimation->setPropertyName("truckPos");
    moveAnimation->setStartValue(startPos);
    moveAnimation->setEndValue(endPos);
    moveAnimation->setDuration(travelTime);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    moveAnimation->start();
}
