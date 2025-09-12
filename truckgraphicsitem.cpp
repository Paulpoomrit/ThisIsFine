#include "truckgraphicsitem.h"

#include <QRandomGenerator>

TruckGraphicsItem::TruckGraphicsItem(QGraphicsItem *parent, const QPixmap &pixmap) :
    QObject(),
    QGraphicsPixmapItem(parent),
    moveAnimation(new QPropertyAnimation(this))
{


    moveAnimation->setTargetObject(this);
    moveAnimation->setPropertyName("truckPos");
    moveAnimation->setStartValue(this->pos());
    moveAnimation->setEndValue(QPoint(100,100));
    moveAnimation->setDuration(800);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    moveAnimation->start();

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
