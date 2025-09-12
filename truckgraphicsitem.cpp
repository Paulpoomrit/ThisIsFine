#include "truckgraphicsitem.h"

#include <QRandomGenerator>

TruckGraphicsItem::TruckGraphicsItem(QGraphicsItem *parent, const QPixmap &pixmap, const std::vector<TileGraphicsItem *> parentTileBoard) :
    QObject(),
    QGraphicsPixmapItem(parent),
    parentTileBoard(parentTileBoard),
    moveAnimation(new QPropertyAnimation(this))
{
    moveTo(0,60,1600); // test

    // connect with the tile graphics

    // QSoundEffect *carEffect = new QSoundEffect(this);
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

    connect(moveAnimation, &QPropertyAnimation::finished, this, [=]() {
        qDebug() << "arrived";

        // delay and commit suicide
        QTimer::singleShot(100, this, [this]() {
            delete this;
        });
    });

    moveAnimation->start();
}
