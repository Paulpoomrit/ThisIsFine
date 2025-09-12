#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include "SpawnMode.h"
#include "flame.h"
#include "soundcue.h"
#include "tile.h"
#include "tilestates.h"
#include "treegraphicsitem.h"

class TileGraphicsItem : public QGraphicsObject

{
    Q_OBJECT
public:
    explicit TileGraphicsItem(QGraphicsObject *parent = nullptr,
                              const TileState tileState = TileState::IDLE,
                              const QSize &tileSize = QSize(50,50),
                              SoundCue* parentSoundCue = nullptr,
                              const int& numTree = 5,
                              Tile* mainTile = nullptr);
    TileState getCurrentTileState() const;
    void setCurrentTileState(TileState newCurrentTileState);

signals:
    void pressed();
    void hoveredEntered();
    void hoveredLeft();

public slots:
    void handleStateChanged(TileState newState, TileState oldState);
    // void handleFireChanged(); // for later smoke effect

private:
    Tile* mainTile;

    QString spriteLocation;
    TileState currentTileState;
    QSize tileSize;
    QPixmap *tileSprite;

    QPixmap *idleSprite;
    QPixmap *highlightSprite;
    QPixmap *clickedEffectSprite;
    QPixmap *fireTruckSprite;
    QGraphicsPixmapItem *overlayItem;

    SoundCue *soundCue;

    TileGraphicalState currentTileGraphicalState;
    SpawnMode currentSpawnMode;

    std::vector<TreeGraphicsItem*> treeItems;
    std::vector<Flame*> flameItems;
    const int numTree;
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    TileGraphicalState getCurrentTileGraphicalState() const;
    void setCurrentTileGraphicalState(TileGraphicalState newCurrentTileGraphicalState);
    void populateTrees();

    std::vector<TreeGraphicsItem *> getTreeItems() const;
    void setTreeItems(const std::vector<TreeGraphicsItem *> &newTreeItems);
    void setVisibleTreeItems(const bool &isVisible);

    std::vector<Flame *> getFlameItems() const;
    void setFlameItems(const std::vector<Flame *> &newFlameItems);
    void setVisibleFlameItems(const bool &isVisible);

    void setOverlayMode(TileGraphicalState tileState = TileGraphicalState::TILE_DEFAULT);
    SpawnMode getCurrentSpawnMode() const;
    void setCurrentSpawnMode(SpawnMode newCurrentSpawnMode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // TILEGRAPHICSITEM_H
