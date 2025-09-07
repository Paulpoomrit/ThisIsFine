#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>

class TileGraphicsItem : public QGraphicsPixmapItem
{
public:
    explicit TileGraphicsItem(QGraphicsItem *parent = nullptr);
};

#endif // TILEGRAPHICSITEM_H
