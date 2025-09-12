#ifndef TRUCKGRAPHICSITEM_H
#define TRUCKGRAPHICSITEM_H

#include "tile.h"
#include "tilegraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>

class TruckGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint truckPos READ getTruckPos WRITE setTruckPos NOTIFY truckPosChanged FINAL)
public:
    explicit TruckGraphicsItem(QGraphicsItem *parent = nullptr,
                               const QPixmap &pixmap = QPixmap(":/tiles/Content/Tiles/tile_0097.png"),
                               const std::vector<TileGraphicsItem*> parentTileBoard = {});
    QPoint getTruckPos() const;
    void setTruckPos(QPoint newTruckPos);

    void moveTo(int startIndex, int stopIndex, int travelTime);
    void readyToConnectToScene();

public slots:

signals:
    void truckSpawned(const std::vector<Tile*>& tileboard,
                      int startIndex,
                      int width,
                      int height,
                      int speed);
    void truckPosChanged(QPoint);
private:
    std::vector<TileGraphicsItem*> parentTileBoard;
    QPoint truckPos;
    QPropertyAnimation *moveAnimation;
    int speed;
};

#endif // TRUCKGRAPHICSITEM_H
