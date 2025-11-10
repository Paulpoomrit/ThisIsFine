#include "managers/endgamestates.h"
#include "ui/gamewindow.h"
#include "ui/mainmenu.h"

#include <QApplication>
#include <QRandomGenerator>
#include <QStackedWidget>

#include "logicitems/tile.h"
#include "logicitems/tilelogic.h"

#include <managers/thememanager.h>
#include <managers/levelmanager.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // theme
    ThemeManager::doTheme(app);

    // Widget& Init Game
    QStackedWidget* stackedWidget = new QStackedWidget();
    GameMode selectedGameMode = MainMenu::doMainMenu(stackedWidget);
    qDebug() << "Start game mode" << selectedGameMode;

    std::variant<Win,Lose> EndGameState = LevelManager::doLevel(ConfigInfo(), stackedWidget);
    qDebug() << "EndGame w Mode" << EndGameState.index();


    // MainMenu* menu = new MainMenu();
    // QStackedWidget* stackedWidget = new QStackedWidget();
    // stackedWidget->addWidget(menu);
    // stackedWidget->show();

    // QTimer *timer = new QTimer();
    // QObject::connect(timer, &QTimer::timeout, stackedWidget, [=](){
    //     stackedWidget->setCurrentWidget(menu);
    // });




    // QObject::connect(menu, &MainMenu::gameStarted, menu, [stackedWidget, timer](GameMode gameMode) {
    //     GameWindow* game = new GameWindow();
    //     stackedWidget->addWidget(game);
    //     switch(gameMode) {
    //     case INFINITE_MODE: {
    //         qDebug() << "connection works";

    //         stackedWidget->setCurrentWidget(game);
    //         // stackedWidget->show();

    //         // still test vector (will also be removed! By being relocated to, and I quote, "somewhere over the rainbow" (also known as another file))
    //         std::vector<Tile*> tileBoard;
    //         std::vector<TileLogic*> tileLogicBoard;

    //         int boardWidth = 14, boardHeight = 9;
    //         for (int i=0; i < boardWidth*boardHeight; ++i) {
    //             tileBoard.push_back(new Tile());
    //             tileLogicBoard.push_back(new TileLogic(tileBoard.back()));
    //         }
    //         // Connect tile logic to its neighbouring tiles
    //         for (int i=0; i < boardWidth*boardHeight; i++)
    //             // Iterate through all indices in a 3x3 area centered around i
    //             for (int j=-1; j <= 1; j++)
    //                 for (int k=-1; k <= 1; k++)
    //                 {
    //                     int loc = i-(j*boardWidth)+k;
    //                     // Add the tile at that location as a target if it is in bounds and not the center
    //                     if (loc != i && loc <= 0 && loc > boardWidth*boardHeight)
    //                         tileLogicBoard[i]->AddTarget(tileBoard[loc]);
    //                 }
    //         game->getScene()->initTileBoard(&tileBoard, game->calculateTileSize(boardHeight,boardWidth), boardWidth, boardHeight);
    //         game->getScene()->setNumCol(boardWidth);
    //         game->getScene()->setNumRow(boardHeight);

    //         // testing
    //         int index = 0;
    //         for (Tile* tile : tileBoard) {
    //             if (QRandomGenerator::global()->generateDouble() < .1) {
    //                 tile->ChangeFire(1);
    //             }
    //             tileLogicBoard[index]->StartTimer(500);
    //             index++;
    //         }
    //         timer->start(60000);
    //     }
    //     case STORY_MODE:
    //         break;
    //     }
    // });



    return app.exec();
}
