#ifndef TRUCKGRAPHICSITEM_H
#define TRUCKGRAPHICSITEM_H

#include "tile.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class TruckGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit TruckGraphicsItem(QGraphicsItem *parent = nullptr);
public slots:
    // void moveTo(int startIndex, int stopIndex, int travelTime);
signals:
    void truckSpawned(std::vector<Tile*>& tileboard,
                      int startIndex,
                      int width,
                      int height,
                      int speed);
private:
};

#endif // TRUCKGRAPHICSITEM_H
