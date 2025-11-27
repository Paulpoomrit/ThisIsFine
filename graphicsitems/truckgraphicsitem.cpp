#include "truckgraphicsitem.h"
#include <QRandomGenerator>

TruckGraphicsItem::TruckGraphicsItem(QGraphicsItem *parent,
                               const QPixmap &pixmap,
                               const std::vector<TileGraphicsItem*> parentTileBoard) :
    QObject(),
    QGraphicsPixmapItem(parent),
    parentTileBoard(parentTileBoard),
    moveAnimation(new QPropertyAnimation(this)),
    speed(100)
{
    QSoundEffect *carEffect = new QSoundEffect(this);
    carEffect->setSource(QUrl::fromLocalFile(":/SFX/Content/SFX/MAD ROBOT Sound Lab - Vintage Motorcycle - Idling Engine Up Close.wav"));

    carEffect->setVolume(0.1);
    carEffect->play();
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
    qDebug() << "move TO" << stopIndex << " From: " << startIndex;
    // Get pos for the starting tile
    QPointF startPos = parentTileBoard[startIndex]->pos();
    QPointF endPos = parentTileBoard[stopIndex]->pos();

    moveAnimation->setTargetObject(this);
    moveAnimation->setPropertyName("truckPos");
    moveAnimation->setStartValue(startPos);
    moveAnimation->setEndValue(endPos);
    moveAnimation->setDuration(travelTime);
    // moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(moveAnimation, &QPropertyAnimation::finished, this, [=]() {
        qDebug() << "arrived";

        // delay and commit suicide
        QTimer::singleShot(100, this, [this]() {
            delete this;
        });
    });
    moveAnimation->start();
    disconnect(tilePressedConnection);
}
