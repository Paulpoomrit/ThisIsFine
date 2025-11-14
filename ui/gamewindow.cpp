#include "gamewindow.h"
#include "gamescene.h"
#include "ui_gamewindow.h"
#include <QtGui/qevent.h>

namespace GameWindowConfig {
constexpr QSize TILE_ERROR_BOUND = QSize(10,10);
}

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    qDebug() << QPalette();
    ui->setupUi(this);

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    connect(ui->fireTruckPushButton, &QPushButton::clicked, this, [this](){
        handleGameModeChagned(SpawnMode::FIRE_TRUCK);
    });
    connect(ui->helicopterPushButton, &QPushButton::clicked, this, [this](){
        handleGameModeChagned(SpawnMode::HELICOPTER);
    });
    connect(ui->planePushButton, &QPushButton::clicked, this, [this](){
        handleGameModeChagned(SpawnMode::PLANE);
    });
    connect(ui->canclePushButton, &QPushButton::clicked, this, [this](){
        handleGameModeChagned(SpawnMode::NONE);
    });
}

GameWindow::~GameWindow()
{
    delete ui;
}

GameScene *GameWindow::getScene()
{
    return scene;
}

QSize GameWindow::calculateTileSize(int numRow, int numCol) const
{

    QSize tileSize;
    QSizeF viewSize = ui->graphicsView->sceneRect().size() + GameWindowConfig::TILE_ERROR_BOUND;

    tileSize.setWidth(viewSize.width()/numCol);
    tileSize.setHeight(viewSize.height()/numRow);
    return tileSize;
}

void GameWindow::handleGameModeChagned(const SpawnMode &spawnMode)
{
    qDebug() << "Spawn Mode: " << &spawnMode;
    this->scene->setCurrentSpawnMode(spawnMode);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QMainWindow::resizeEvent(event);
    if(ui->graphicsView->scene()) {

        ui->graphicsView->scene()->setSceneRect(sceneRectHint);
        qDebug() <<  ui->graphicsView->scene()->sceneRect();
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect());
    }
}

// we delay the initialization of the tileBoard untill
// we're sure that the window is visible
// so the size() gives the correct result.
void GameWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    sceneRectHint = QRect(0,0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
    scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->show();
}
