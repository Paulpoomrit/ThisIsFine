#include "tilegraphicsitem.h"
#include "SpawnMode.h"
#include "firetruck.h"
#include "truckgraphicsitem.h"

#include <QPainter>
#include <QPixmap>
#include <QtWidgets/qgraphicsscene.h>
#include <qrandom.h>
#include <QRandomGenerator>

TileGraphicsItem::TileGraphicsItem(QGraphicsObject *parent,
                                   const TileState tileState,
                                   const QSize &tileSize,
                                   SoundCue *parentSoundCue,
                                   const int& numTree,
                                   Tile* mainTile,
                                   const std::vector<TileGraphicsItem *> &parentTileBoard) :
    QGraphicsObject(parent),
    parentTileBoard(parentTileBoard),
    mainTile(mainTile),
    currentTileState(tileState),
    tileSize(tileSize),
    tileSprite(new QPixmap),
    idleSprite(new QPixmap),
    highlightSprite(new QPixmap(":/tiles/Content/Tiles/tile_0061.png")),
    clickedEffectSprite(new QPixmap(":/tiles/Content/Tiles/tile_0079.png")),
    fireTruckSprite(new QPixmap(":/tiles/Content/Tiles/tile_0097.png")),
    planeSprite(new QPixmap(":/tiles/Content/Tiles/tile_0097.png")),
    helicopterSprite(new QPixmap(":/tiles/Content/Tiles/tile_0097.png")),
    overlayItem(new QGraphicsPixmapItem(*idleSprite)),
    soundCue(parentSoundCue),
    currentTileGraphicalState(TileGraphicalState::TILE_DEFAULT),
    currentSpawnMode(SpawnMode::NONE),
    treeItems(),
    numTree(numTree)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, false);
    std::vector<QString> tileSprites = {":/tiles/Content/Tiles/tile_0000.png",
                                        ":/tiles/Content/Tiles/tile_0000.png",
                                        ":/tiles/Content/Tiles/tile_0001.png"};
    int randomIndex = QRandomGenerator::global()->bounded(static_cast<int>(tileSprites.size()));
    QPixmap pixmap(tileSprites.at(randomIndex));
    spriteLocation = tileSprites.at(randomIndex);
    *tileSprite = pixmap.scaled(tileSize.width(), tileSize.height());
    *idleSprite = *tileSprite;
    *highlightSprite = highlightSprite->scaled(tileSize.width(), tileSize.height());
    *clickedEffectSprite = clickedEffectSprite->scaled(tileSize.width(), tileSize.height());

    std::vector<QString> truckSprites = {":/tiles/Content/Tiles/tile_0097.png",
                                         ":/tiles/Content/Tiles/tile_0115.png",
                                         ":/tiles/Content/Tiles/tile_0133.png",
                                         ":/tiles/Content/Tiles/tile_0151.png",
                                         ":/tiles/Content/Tiles/tile_0169.png"};
    int vehicleRandomIndex = QRandomGenerator::global()->bounded(static_cast<int>(truckSprites.size()));
    QPixmap truckPixmap(truckSprites.at(vehicleRandomIndex));
    *fireTruckSprite  = truckPixmap.scaled(tileSize.width(), tileSize.height());

    std::vector<QString> planeSprites = {":/tiles/Content/Tiles/tile_0136.png",
                                         ":/tiles/Content/Tiles/tile_0154.png",
                                         ":/tiles/Content/Tiles/tile_0172.png",
                                         ":/tiles/Content/Tiles/tile_0100.png",
                                         ":/tiles/Content/Tiles/tile_0118.png"};
    QPixmap planePixmap(planeSprites.at(vehicleRandomIndex));
    *planeSprite  = planePixmap.scaled(tileSize.width(), tileSize.height());

    std::vector<QString> helicopterSprites = {":/tiles/Content/Tiles/tile_0101.png",
                                             ":/tiles/Content/Tiles/tile_0119.png",
                                             ":/tiles/Content/Tiles/tile_0137.png",
                                             ":/tiles/Content/Tiles/tile_0155.png",
                                             ":/tiles/Content/Tiles/tile_0173.png"};
    QPixmap helicopterPixmap(helicopterSprites.at(vehicleRandomIndex));
    *helicopterSprite  = helicopterPixmap.scaled(tileSize.width(), tileSize.height());

    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

    connect(mainTile, &Tile::StateChanged, this, &TileGraphicsItem::handleStateChanged);
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
    update();

    switch (newCurrentTileState) {
    case TileState::BURNING :
        setVisibleFlameItems(true);
        break;
    case TileState::DEAD:
        setVisibleFlameItems(false);
        setVisibleTreeItems(false);
        break;
    case TileState::IDLE:
        setVisibleFlameItems(false);
        break;
    }
}

void TileGraphicsItem::handleStateChanged(TileState newState, TileState oldState)
{
    Q_UNUSED(oldState);
    setCurrentTileState(newState);
}

QSize TileGraphicsItem::getTileSize() const
{
    return tileSize;
}

void TileGraphicsItem::setTileSize(const QSize &newTileSize)
{
    tileSize = newTileSize;
}

SpawnMode TileGraphicsItem::getCurrentSpawnMode() const
{
    return currentSpawnMode;
}

void TileGraphicsItem::setCurrentSpawnMode(SpawnMode newCurrentSpawnMode)
{
    currentSpawnMode = newCurrentSpawnMode;
}

std::vector<Flame *> TileGraphicsItem::getFlameItems() const
{
    return flameItems;
}

void TileGraphicsItem::setFlameItems(const std::vector<Flame *> &newFlameItems)
{
    flameItems = newFlameItems;
}

void TileGraphicsItem::setVisibleFlameItems(const bool &isVisible)
{
    for (Flame *flame : flameItems) {
        flame->setVisible(isVisible);
    }
}

void TileGraphicsItem::setOverlayMode(TileGraphicalState tileState)
{
    if (this->getCurrentSpawnMode() == SpawnMode::NONE) {
        switch(tileState) {
        case TileGraphicalState::TILE_DEFAULT:
            overlayItem->setOpacity(0);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_HOVERED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*highlightSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_PRESSED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*clickedEffectSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        }
    } else if (this->getCurrentSpawnMode() == SpawnMode::FIRE_TRUCK) {
        switch(tileState) {
        case TileGraphicalState::TILE_DEFAULT:
            overlayItem->setOpacity(0);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_HOVERED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*fireTruckSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_PRESSED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*clickedEffectSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);

            TruckGraphicsItem* fireTruck = new TruckGraphicsItem(nullptr, *fireTruckSprite, parentTileBoard);
            fireTruck->setPixmap(*fireTruckSprite);
            this->scene()->addItem(fireTruck);
            fireTruck->setPos(this->pos());
            fireTruck->setZValue(90);
            fireTruck->readyToConnectToScene();

            this->setCurrentSpawnMode(SpawnMode::NONE);

            break;
        }
    }   else if (this->getCurrentSpawnMode()  == SpawnMode::PLANE) {
        switch(tileState) {
        case TileGraphicalState::TILE_DEFAULT:
            overlayItem->setOpacity(0);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_HOVERED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*planeSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_PRESSED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*clickedEffectSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);

            TruckGraphicsItem* fireTruck = new TruckGraphicsItem(nullptr, *planeSprite, parentTileBoard);
            fireTruck->setPixmap(*planeSprite);
            this->scene()->addItem(fireTruck);
            fireTruck->setPos(this->pos());
            fireTruck->setZValue(90);
            fireTruck->readyToConnectToScene();

            this->setCurrentSpawnMode(SpawnMode::NONE);

            break;
        }
    }   else if (this->getCurrentSpawnMode()  == SpawnMode::HELICOPTER) {
        switch(tileState) {
        case TileGraphicalState::TILE_DEFAULT:
            overlayItem->setOpacity(0);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_HOVERED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*helicopterSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);
            break;
        case TileGraphicalState::TILE_PRESSED:
            overlayItem->setOpacity(1);
            overlayItem->setPixmap(*clickedEffectSprite);
            overlayItem->setPos(this->pos());
            overlayItem->setZValue(100);
            overlayItem->scene() ? void(0) : this->scene()->addItem(overlayItem);

            TruckGraphicsItem* fireTruck = new TruckGraphicsItem(nullptr, *helicopterSprite, parentTileBoard);
            fireTruck->setPixmap(*helicopterSprite);
            this->scene()->addItem(fireTruck);
            fireTruck->setPos(this->pos());
            fireTruck->setZValue(90);
            fireTruck->readyToConnectToScene();

            this->setCurrentSpawnMode(SpawnMode::NONE);

            break;
        }
    }
}

std::vector<TreeGraphicsItem *> TileGraphicsItem::getTreeItems() const
{
    return treeItems;
}

void TileGraphicsItem::setTreeItems(const std::vector<TreeGraphicsItem *> &newTreeItems)
{
    treeItems = newTreeItems;
}

void TileGraphicsItem::setVisibleTreeItems(const bool &isVisible)
{
    for (TreeGraphicsItem *tree : treeItems) {
        tree->setVisible(isVisible);
    }
}

TileGraphicalState TileGraphicsItem::getCurrentTileGraphicalState() const
{
    return currentTileGraphicalState;
}

void TileGraphicsItem::setCurrentTileGraphicalState(TileGraphicalState newCurrentTileGraphicalState)
{
    currentTileGraphicalState = newCurrentTileGraphicalState;
}

void TileGraphicsItem::populateTrees()
{
    for (int i = 0; i < numTree; i++) {
        TreeGraphicsItem *treeItem = new TreeGraphicsItem(this);
        treeItem->setScale(1);
        int randomX = QRandomGenerator::global()->bounded(tileSize.width());
        int randomY = QRandomGenerator::global()->bounded(tileSize.height());
        treeItem->setPos(randomX, randomY);
        treeItem->setZValue(50);
        treeItems.push_back(treeItem);
    }
}

QRectF TileGraphicsItem::boundingRect() const
{
    return QRectF(0,0,tileSize.width(), tileSize.height());
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF overlayRect(this->boundingRect());
    QBrush brush;
    QColor tileColorOverlay = Qt::red;

    switch(currentTileState) {
    case TileState::IDLE:
        painter->drawPixmap(QPoint(0,0), *tileSprite);
        tileColorOverlay = Qt::darkGreen;
        tileColorOverlay.setAlphaF(0.25);
        brush.setColor(tileColorOverlay);
        brush.setStyle(Qt::Dense3Pattern);
        painter->fillRect(overlayRect, brush);
        break;
    case TileState::BURNING:
        painter->drawPixmap(QPoint(0,0), *tileSprite);
        tileColorOverlay.setAlphaF(0.8);
        brush.setColor(tileColorOverlay);
        brush.setStyle(Qt::Dense3Pattern);
        painter->fillRect(overlayRect, brush);
        break;
    case TileState::DEAD:
        painter->drawPixmap(QPoint(0,0), *tileSprite);
        tileColorOverlay = Qt::black;
        tileColorOverlay.setAlphaF(0.8);
        brush.setColor(tileColorOverlay);
        brush.setStyle(Qt::Dense1Pattern);
        painter->fillRect(overlayRect, brush);
        break;
    }
}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if (soundCue) {
        soundCue->playSFX(SFX::PRESSED, 1);
    }
    setCurrentTileGraphicalState(TileGraphicalState::TILE_PRESSED);
    setOverlayMode(TileGraphicalState::TILE_PRESSED);

    mainTile->ChangeFire(-1);

    emit pressed(this->getCurrentSpawnMode());
}

void TileGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    if (soundCue) {
        soundCue->playSFX(SFX::DIRT, 0.1);
    }
    setCurrentTileGraphicalState(TileGraphicalState::TILE_HOVERED);
    setOverlayMode(TileGraphicalState::TILE_HOVERED);
    update();
}

void TileGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    // *tileSprite = *idleSprite;
    setCurrentTileGraphicalState(TileGraphicalState::TILE_DEFAULT);
    setOverlayMode(TileGraphicalState::TILE_DEFAULT);
    update();
}
