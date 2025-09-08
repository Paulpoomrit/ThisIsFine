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
    qDebug() << ui->graphicsView->size();
}

void GameWindow::showEvent(QShowEvent *event)
{
    qDebug() << ui->graphicsView->size();
    GameScene *scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    std::vector<Tile*> test;
    for (int i = 0; i < 64; ++i) {
        test.push_back(new Tile());
    }
    scene->initTileBoard(test, calculateTileSize(8,8), 8,8);
    ui->graphicsView->show();
}
