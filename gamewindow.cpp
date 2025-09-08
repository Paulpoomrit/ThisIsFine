#include "gamewindow.h"
#include "gamescene.h"
#include "ui_gamewindow.h"
#include "tilegraphicsitem.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

GameScene GameWindow::getScene()
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

void GameWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QMainWindow::resizeEvent(event);
    if(ui->graphicsView->scene()) {
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
    scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    // test vector (will be removed!)
    std::vector<Tile*> test;
    for (int i = 0; i < 64; ++i) {
        test.push_back(new Tile());
    }

    scene->initTileBoard(test, calculateTileSize(8,8), 8);
    ui->graphicsView->show();
}
