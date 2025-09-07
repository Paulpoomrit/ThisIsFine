#include "gamewindow.h"
#include "gamescene.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    GameScene *scene = new GameScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

GameWindow::~GameWindow()
{
    delete ui;
}
