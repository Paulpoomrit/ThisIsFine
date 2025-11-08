#include "firetruck.h"

#include <QObject>
#include <QTimer>
#include <QtCore/qdebug.h>
#include <vector>
#include <list>

#include "tile.h"

FireTruck::FireTruck(
    std::vector<Tile*>* board,
    const int spawnIndex,
    const int boardWidth,
    const int boardHeight,
    const int extinguishStrength,
    const int extinguishRange
    )
    : board(board)
    , spawnIndex(spawnIndex)
    , extinguishStrength(extinguishStrength)
    , extinguishRowCount(0)
{
    int minRange, maxRange;
    int sOFSOE; // spawnOffsetFromStartOfEdge

    // Truck travels horizontally
    if (spawnIndex % boardWidth == 0 || spawnIndex % boardWidth == boardWidth-1)
    {
        // Get tiles to extinguish
        sOFSOE = spawnIndex / boardWidth;
        minRange = qMax(0, sOFSOE - extinguishRange);
        maxRange = qMin(boardHeight-1, sOFSOE+extinguishRange);
        // Truck travels east
        if (spawnIndex % boardWidth == 0)
        {
            endIndex = spawnIndex + boardWidth-1;
            for (int i=0; i < boardWidth; i++)
                for (int j=minRange; j <= maxRange; j++)
                    targetTiles.push_back(j*boardWidth + i);
        }
        // Truck travels west
        else
        {
            endIndex = spawnIndex - (boardWidth-1);
            for (int i=boardWidth-1; i >= 0; i--)
                for (int j=minRange; j <= maxRange; j++)
                    targetTiles.push_back(j*boardWidth + i);
        }

        totalTravelDistance = boardWidth;
    }
    // Truck travels vertically
    else
    {
        // Get tiles to extinguish
        sOFSOE = spawnIndex % boardWidth;
        minRange = qMax(0, sOFSOE - extinguishRange);
        maxRange = qMin(boardWidth-1, sOFSOE+extinguishRange);
        // Truck travels north
        if (spawnIndex / boardWidth == boardHeight-1)
        {
            endIndex = spawnIndex - (boardHeight-1)*boardWidth;
            for (int i=boardHeight-1; i >= 0; i--)
                for (int j=minRange; j <= maxRange; j++)
                    targetTiles.push_back(j + i*boardWidth);
        }
        // Truck travels south
        else
        {
            endIndex = spawnIndex + (boardHeight-1)*boardWidth;
            for (int i=0; i < boardHeight; i++)
                for (int j=minRange; j <= maxRange; j++)
                    targetTiles.push_back(j + i*boardWidth);
        }

        totalTravelDistance = boardHeight;
    }
    extinguishRowCount = maxRange - minRange +1;
}

void FireTruck::StartTraveling(const int msPerTile)
{
    tileTimer = new QTimer(this);
    connect(tileTimer, &QTimer::timeout, this, &FireTruck::ExtinguishRow);
    tileTimer->start(msPerTile);

    emit StartedTraveling(totalTravelDistance*msPerTile, spawnIndex, endIndex);
}

void FireTruck::ExtinguishRow()
{
    qDebug() << "extinguishRow" << board->size();
    // Extinguish a row of fire
    for (int i=0; i < extinguishRowCount; i++)
    {
        //board[64]->ChangeFire(-extinguishStrength);
        (*board)[targetTiles.front()]->ChangeFire(-extinguishStrength);
        targetTiles.pop_front();
    }

    // Check if there is anything left to extinguish
    if (targetTiles.empty())
    {
        tileTimer->stop();
        emit FinishedTraveling();
    }
}
