#include "GameWindow.h"
#include "mainmenu.h"
#include "mainwindow.h"

#include <QApplication>
#include <QStackedWidget>

#include "tile.h"
#include "tileLogic.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // theme
    app.setStyle("Fusion");

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    // darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);

    QStackedWidget* stackedWidget = new QStackedWidget();

    MainMenu* menu = new MainMenu();
    GameWindow* game = new GameWindow();
    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(game);

    stackedWidget->setCurrentWidget(menu);
    stackedWidget->show();

    QObject::connect(menu, &MainMenu::gameStarted, [stackedWidget, game](GameMode gameMode) {
        switch(gameMode) {
        case INFINITE_MODE: {
            qDebug() << "connection works";

            stackedWidget->setCurrentWidget(game);
            stackedWidget->show();

            // still test vector (will also be removed! By being relocated to, and I quote, "somewhere over the rainbow" (also known as another file))
            std::vector<Tile*> tileBoard;
            std::vector<TileLogic*> tileLogicBoard;

            int boardWidth = 14, boardHeight = 9;
            for (int i=0; i < boardWidth*boardHeight; ++i) {
                tileBoard.push_back(new Tile());
                tileLogicBoard.push_back(new TileLogic(tileBoard.back()));
            }
            // Connect tile logic to its neighbouring tiles
            for (int i=0; i < boardWidth*boardHeight; i++)
                // Iterate through all indices in a 3x3 area centered around i
                for (int j=-1; j <= 1; j++)
                    for (int k=-1; k <= 1; k++)
                    {
                        int loc = i-(j*boardWidth)+k;
                        // Add the tile at that location as a target if it is in bounds and not the center
                        if (loc != i && loc <= 0 && loc > boardWidth*boardHeight)
                            tileLogicBoard[i]->AddTarget(tileBoard[loc]);
                    }
            game->getScene()->initTileBoard(tileBoard, game->calculateTileSize(boardHeight,boardWidth), boardWidth);

            // testing
            int index = 0;
            for (Tile* tile : tileBoard) {
                tile->ChangeFire(1);
                tileLogicBoard[index]->StartTimer(500);
                index++;
            }
        }
        case STORY_MODE:
            break;
        }
    });



    return app.exec();
}
