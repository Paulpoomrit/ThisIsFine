#include "GameWindow.h"
#include "mainwindow.h"

#include <QApplication>
#include "mainmenu.h";

#include "tile.h"
#include "tileLogic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    // still test vector (will also be removed! By being relocated to, and I quote, "somewhere over the rainbow" (also known as another file))
    std::vector<Tile*> tileBoard;
    std::vector<TileLogic*> tileLogicBoard;
    int boardWidth = 8, boardHeight = 8;
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
    w.getScene()->initTileBoard(tileBoard, w.calculateTileSize(8,8), boardWidth);

    // testing
    int index = 0;
    for (Tile* tile : tileBoard) {
        tile->ChangeFire(1);
        tileLogicBoard[index]->StartTimer(500);
        index++;
    }

    return a.exec();
}
