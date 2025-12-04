#ifndef FIRETRUCK_H
#define FIRETRUCK_H

#include <QObject>
#include <QTimer>
#include <vector>
#include <list>

#include "tile.h"

class FireTruck : public QObject
{
    Q_OBJECT
public:
    FireTruck(std::vector<Tile*>*, const int, const int, const int, const int = 1, const int = 1);
    void StartTraveling(const int);

private slots:
    void ExtinguishRow();

signals:
    void StartedTraveling(int totalTime, int startIndex, int endIndex);
    void FinishedTraveling();

private:
    std::vector<Tile*>* board;
    std::list<int> targetTiles; // List of offsets for tiles that will be affected
    QTimer* tileTimer;
    int spawnIndex;
    int endIndex;
    int extinguishStrength;
    int extinguishRowCount;
    int totalTravelDistance;
};

#endif // FIRETRUCK_H
