#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
#include <QtGui/qevent.h>

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

    // constraint aspect ratio
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
}

MainMenu::~MainMenu()
{
    delete ui;
}

QSize MainMenu::sizeHint() const
{
    return QSize(1920, heightForWidth(1920));
}

int MainMenu::heightForWidth(int width) const
{
    return width * 9/16;
}

void MainMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
