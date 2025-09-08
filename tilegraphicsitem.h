#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include "soundcue.h"
#include "tilestates.h"

class TileGraphicsItem : public QGraphicsObject

{
    Q_OBJECT
public:
    explicit TileGraphicsItem(QGraphicsObject *parent = nullptr,
                              const TileState tileState = TileState::IDLE,
                              const QSize &tileSize = QSize(50,50),
                              SoundCue* parentSoundCue = nullptr);
    TileState getCurrentTileState() const;
    void setCurrentTileState(TileState newCurrentTileState);

signals:
    void pressed();
    void hoveredEntered();
    void hoveredLeft();

private:
    QString spriteLocation;
    TileState currentTileState;
    QSize tileSize;
    QPixmap *tileSprite;

    QPixmap *idleSprite;
    QPixmap *highlightSprite;
    QPixmap *clickedEffectSprite;
    SoundCue *soundCue;

    TileGraphicalState currentTileGraphicalState;
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    TileGraphicalState getCurrentTileGraphicalState() const;
    void setCurrentTileGraphicalState(TileGraphicalState newCurrentTileGraphicalState);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // TILEGRAPHICSITEM_H
