#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include "tilestates.h"

class TileGraphicsItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TileGraphicsItem(QGraphicsObject *parent = nullptr, const TileState tileState = TileState::IDLE, const QSize &tileSize = QSize(50,50));
    TileState getCurrentTileState() const;
    void setCurrentTileState(TileState newCurrentTileState);

signals:
    void pressed();
    void hoveredEntered();
    void hoveredLeft();

private:
    TileState currentTileState;
    QSize tileSize;
    QPixmap *tileSprite;

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TILEGRAPHICSITEM_H
