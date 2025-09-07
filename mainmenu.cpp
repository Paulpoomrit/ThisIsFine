#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->storyModeButton, &RetroButton::clicked, this, [this](){
        qDebug() << "Start game mode: STORY";
        emit gameStarted(GameMode::STORY_MODE);
    });
    connect(ui->infiniteModeButton, &RetroButton::clicked, this, [this](){
        qDebug() << "Start game mode: INFINITE";
        emit gameStarted(GameMode::INFINITE_MODE);
    });
    connect(ui->exitButton, &RetroButton::clicked, this, []() {
        QApplication::quit();
    });
}

MainMenu::~MainMenu()
{
    delete ui;
}
