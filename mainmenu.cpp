#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->storyModeButton, &QPushButton::clicked, this, [this]() {startGame(STORY_MODE);});
    connect(ui->infiniteModeButton, &QPushButton::clicked, this, [this]() {startGame(INFINITE_MODE);});
    connect(ui->exitButton, &QPushButton::clicked, this, &MainMenu::exitGame);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::startGame(GameMode gameMode)
{
    qDebug() << "Starting game with game mode: " << gameMode;
    emit gameStarted(gameMode);
}

void MainMenu::exitGame()
{
    QApplication::quit();
}
