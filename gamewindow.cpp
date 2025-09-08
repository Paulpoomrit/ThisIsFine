#include "gamewindow.h"
#include "gamescene.h"
#include "ui_gamewindow.h"
#include "tilegraphicsitem.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    GameScene *scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    qreal sceneWidth = ui->graphicsView->width();
    qreal sceneHeight = ui->graphicsView->height();
    ui->graphicsView->setSceneRect(0, 0, sceneWidth, sceneHeight);
    ui->graphicsView->show();
}

GameWindow::~GameWindow()
{
    delete ui;
}
