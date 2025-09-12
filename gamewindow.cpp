#include "gamewindow.h"
#include "gamescene.h"
#include "ui_gamewindow.h"
#include "tilegraphicsitem.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->fireTruckPushButton, &QPushButton::clicked, this, [this](){
        handleGameModeChagned(SpawnMode::FIRE_TRUCK);
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
    QSize viewSize = ui->graphicsView->size();
    qDebug() << viewSize;
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
    qDebug() << ui->graphicsView->size();
    sceneRectHint = QRect(0,0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
    scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->show();
}
