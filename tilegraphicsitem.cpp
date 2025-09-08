#include "tilegraphicsitem.h"

#include <QPainter>
#include <QPixmap>
#include <qrandom.h>

TileGraphicsItem::TileGraphicsItem(QGraphicsObject *parent,
                                   const TileState tileState,
                                   const QSize &tileSize,
                                   SoundCue *parentSoundCue) :
    QGraphicsObject(parent),
    currentTileState(tileState),
    tileSize(tileSize),
    tileSprite(new QPixmap),
    idleSprite(new QPixmap),
    highlightSprite(new QPixmap(":/tiles/Content/Tiles/tile_0061.png")),
    clickedEffectSprite(new QPixmap(":/tiles/Content/Tiles/tile_0079.png")),
    soundCue(parentSoundCue),
    currentTileGraphicalState(TileGraphicalState::TILE_DEFAULT)
{
    std::vector<QString> tileSprites = {":/tiles/Content/Tiles/tile_0000.png",
                                        ":/tiles/Content/Tiles/tile_0001.png",
                                        ":/tiles/Content/Tiles/tile_0002.png"};
    int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(tileSprites.size()));
    QPixmap pixmap(tileSprites.at(randomIndex));
    spriteLocation = tileSprites.at(randomIndex);
    *tileSprite = pixmap.scaled(tileSize.width(), tileSize.height());
    *idleSprite = *tileSprite;
    *highlightSprite = highlightSprite->scaled(tileSize.width(), tileSize.height());
    *clickedEffectSprite = clickedEffectSprite->scaled(tileSize.width(), tileSize.height());

    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
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
}

TileGraphicalState TileGraphicsItem::getCurrentTileGraphicalState() const
{
    return currentTileGraphicalState;
}

void TileGraphicsItem::setCurrentTileGraphicalState(TileGraphicalState newCurrentTileGraphicalState)
{
    currentTileGraphicalState = newCurrentTileGraphicalState;
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

    switch(currentTileGraphicalState) {
    case TileGraphicalState::TILE_PRESSED:
        painter->drawPixmap(QPoint(0,0), *clickedEffectSprite);
        painter->drawPixmap(QPoint(0,0), *highlightSprite);
        break;
    case TileGraphicalState::TILE_HOVERED:
        painter->drawPixmap(QPoint(0,0), *highlightSprite);
        break;

    case TileGraphicalState::TILE_DEFAULT:
        painter->drawPixmap(QPoint(0,0), *idleSprite);
        break;
    }


}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    // if (soundCue) {
    //     soundCue->playSFX(SFX::PRESSED, 1);
    // }
    // QPainter *painter = new QPainter(tileSprite);
    // painter->drawPixmap(QPoint(0,0), *clickedEffectSprite);
    // painter->drawPixmap(QPoint(0,0), *highlightSprite);
    setCurrentTileGraphicalState(TileGraphicalState::TILE_PRESSED);
    emit pressed();
}

void TileGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // if (soundCue) {
    //     soundCue->playSFX(SFX::HOVERED, 1);
    // }
    // QPainter *painter = new QPainter(tileSprite);
    // painter->drawPixmap(QPoint(0,0), *highlightSprite);
    // painter->end();
    setCurrentTileGraphicalState(TileGraphicalState::TILE_HOVERED);
    update();
}

void TileGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // *tileSprite = *idleSprite;
    setCurrentTileGraphicalState(TileGraphicalState::TILE_DEFAULT);
    update();
}
