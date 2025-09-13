#include "truckgraphicsitem.h"

#include "GameScene.h"
#include "firetruck.h"

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

void TruckGraphicsItem::readyToConnectToScene()
{   
    // connect with the scene to receive the tileIndex
    GameScene* gameScene = qobject_cast<GameScene*>(this->scene());
    qDebug() << this->parent();


    int numCols = gameScene->getNumCol();
    int numRows = gameScene->getNumRow();


    if (gameScene) {
        tilePressedConnection = connect(gameScene, &GameScene::tilePressed, this, [=](const int &tileIndex) {

            std::vector<Tile*> *baseTileBoard = gameScene->getBaseTileBoard();
            QSize tileSize = parentTileBoard[0]->getTileSize();

            fireTruckLogic = new FireTruck(baseTileBoard, tileIndex, numCols, numRows, gameScene->getNumRow());

            connect(fireTruckLogic, &FireTruck::StartedTraveling, this, [=](int totalTravelTime, int spawnIndex, int endIndex){
                qDebug() << "frontend: connect";
                this->moveTo(spawnIndex, endIndex, totalTravelTime);
            });

            fireTruckLogic->StartTraveling(500);

            // emit truckSpawned(baseTileBoard, tileIndex, tileSize.width(), tileSize.height(), speed);

            qDebug() << "spawn at tile no:" << tileIndex;
            // moveTo(tileIndex,60,1600); // test -> will have to be called from the logic side
        });
    } else {
        qDebug() << "game scene not valid:";
    }
}
