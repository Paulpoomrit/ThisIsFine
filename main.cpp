#include "managers/endgamestates.h"
#include "ui/mainmenu.h"
#include <QApplication>
#include <QRandomGenerator>
#include <QStackedWidget>
#include <managers/levelmanager.h>
#include <managers/thememanager.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemeManager::doTheme(app);

    GameMode selectedGameMode = MainMenu::doMainMenu();
    ConfigInfo gameConfig;
    gameConfig.gameMode = selectedGameMode;
    qDebug() << "Start game mode" << selectedGameMode;

    std::variant<Win,Lose> EndGameState = LevelManager::doLevel(gameConfig);
    qDebug() << "EndGame w Mode" << EndGameState.index();

    return app.exec();
}
