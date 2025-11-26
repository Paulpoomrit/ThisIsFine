#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
#include <QtGui/qevent.h>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
    connect(ui->storyModeButton, &RetroButton::clicked, this, [this](){
        emit gameStarted(GameMode::STORY_MODE);
    });
    connect(ui->infiniteModeButton, &RetroButton::clicked, this, [this](){
        emit gameStarted(GameMode::INFINITE_MODE);
    });
    connect(ui->exitButton, &RetroButton::clicked, this, [this]() {
        this->close();
        qApp->exit();
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

GameMode MainMenu::doMainMenu()
{
    MainMenu* mainMenu = new MainMenu();
    mainMenu->show();
    QEventLoop loop;
    GameMode selectedMode;

    QObject::connect(mainMenu, &MainMenu::gameStarted, mainMenu, [&loop, &selectedMode](GameMode gameMode) {
        selectedMode = gameMode;
        loop.quit();
    });

    QObject::connect(mainMenu, &QObject::destroyed, mainMenu, [&loop] {
        loop.quit();
    });

    loop.exec();
    delete mainMenu;
    return selectedMode;
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
