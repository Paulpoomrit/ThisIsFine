#include "flame.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qtimer.h>

Flame::Flame(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    flameSprites(),
    animTimer(new QTimer),
    currentSpriteIndex(0)
{
    FlameSpriteMap allSprites = loadFlameSpritePaths(":/data/flameSprites.json");

    const auto &randomFlameType = getRandomFlameType();
    const auto &paths = allSprites[randomFlameType];
    loadFlameSprites(paths);
    setOffset(0, -flameSprites[0].height() / 2);
    setPixmap(flameSprites[0]);
    animate(10);
}

void Flame::animate(const int &fps)
{
    QEventLoop::connect(animTimer, &QTimer::timeout, this, &Flame::updateToNextSprite);
    float updateTimeInMs = 1000 / fps;
    animTimer->start(updateTimeInMs);
}

FlameSpriteMap Flame::loadFlameSpritePaths(const QString &jsonPath)
{
    FlameSpriteMap spriteMap;
    QFile file(jsonPath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open JSON file:" << jsonPath;
        qDebug() << "Working directory:" << QDir::currentPath();
        return spriteMap;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "Invalid JSON structure!";
        return spriteMap;
    }

    QJsonObject root = doc.object();
    for (auto flameIt = root.begin(); flameIt != root.end(); ++flameIt) {
        FlameType type = stringToFlameType(flameIt.key());
        QJsonArray pathsArray = flameIt.value().toArray();

        std::vector<QString> paths;
        paths.reserve(pathsArray.size());

        for (const auto &val : std::as_const(pathsArray)) {
            paths.push_back((val.toString()));
        }
        spriteMap[type] = std::move(paths);
    }
    return spriteMap;
}

QString Flame::flameTypeToString(FlameType type)
{
    switch (type) {
    case FlameType::FLAME_1:  return "flame_01";
    case FlameType::FLAME_2:  return "flame_02";
    case FlameType::FLAME_9:  return "flame_09";
    case FlameType::FLAME_11: return "flame_11";
    case FlameType::FLAME_12: return "flame_12";
    default:                  return "unknown_flame";
    }
}

FlameType Flame::stringToFlameType(const QString &str)
{
    if (str == "flame_01") return FlameType::FLAME_1;
    if (str == "flame_02") return FlameType::FLAME_2;
    if (str == "flame_09") return FlameType::FLAME_9;
    if (str == "flame_11") return FlameType::FLAME_11;
    if (str == "flame_12") return FlameType::FLAME_12;
    qWarning() << "Unknown flame type string:" << str;
    return FlameType::FLAME_1;
}

FlameType Flame::getRandomFlameType() const
{
    constexpr int flameTypeCount = 5; // Number of enum entries

    int index = QRandomGenerator::global()->bounded(flameTypeCount);
    switch (index) {
    case 0: return FlameType::FLAME_1;
    case 1: return FlameType::FLAME_2;
    case 2: return FlameType::FLAME_9;
    case 3: return FlameType::FLAME_11;
    case 4: return FlameType::FLAME_12;
    default: return FlameType::FLAME_1;
    }
}

void Flame::loadFlameSprites(const std::vector<QString> &pathArray)
{
    flameSprites.clear();
    for (const QString &path: pathArray) {
        QPixmap sprite(path);
        flameSprites.push_back(sprite);
    }
}

void Flame::updateToNextSprite()
{
    if (flameSprites.empty()) {
        return;
    }
    setPixmap(flameSprites[currentSpriteIndex]);
    currentSpriteIndex = (currentSpriteIndex + 1) % flameSprites.size();
}
