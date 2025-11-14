#include "managers/endgamestates.h"
#include "ui/mainmenu.h"

#include <QApplication>
#include <QRandomGenerator>
#include <QStackedWidget>

#include <managers/thememanager.h>
#include <managers/levelmanager.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // theme
    ThemeManager::doTheme(app);

    // Widget& Init Game
    GameMode selectedGameMode = MainMenu::doMainMenu();
    qDebug() << "Start game mode" << selectedGameMode;

    std::variant<Win,Lose> EndGameState = LevelManager::doLevel(ConfigInfo());
    qDebug() << "EndGame w Mode" << EndGameState.index();


    return app.exec();
}
