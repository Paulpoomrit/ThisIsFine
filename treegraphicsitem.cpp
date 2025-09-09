#include "treegraphicsitem.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QElapsedTimer>

TreeGraphicsItem::TreeGraphicsItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    treeSprites(),
    animTimer(new QTimer),
    currentSpriteIndex(0)
{
    qDebug() << "hi im tree!";

    SpriteMap allSprites = loadTreeSpritePaths(":/data/treeSprites.json");

    const auto &paths = allSprites[TreeType::BubblePineTree][TreeColour::GREEN];
    loadTreeSprites(paths);
    setPixmap(treeSprites[0]);
    animate(20);
}

void TreeGraphicsItem::animate(const int &fps)
{
    connect(animTimer, &QTimer::timeout, this, &TreeGraphicsItem::updateToNextSprite);
    float updateTimeInMs = 1000 / fps;
    animTimer->start(updateTimeInMs);
}

void TreeGraphicsItem::stopAnimation()
{
    disconnect(animTimer, &QTimer::timeout, this, &TreeGraphicsItem::updateToNextSprite);
}

SpriteMap TreeGraphicsItem::loadTreeSpritePaths(const QString &jsonPath)
{
    SpriteMap spriteMap;
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
    for (auto treeIt = root.begin(); treeIt != root.end(); ++treeIt) {
        TreeType type = stringToTreeType(treeIt.key());
        QJsonObject colourObj = treeIt.value().toObject();

        QMap<TreeColour, std::vector<QString>> colourMap;

        for (auto colourIt = colourObj.begin(); colourIt != colourObj.end(); ++colourIt) {
            TreeColour colour = stringToTreeColor(colourIt.key());
            QJsonArray pathsArray = colourIt.value().toArray();

            std::vector<QString> paths;
            paths.reserve(pathsArray.size());

            for (const auto &val :  std::as_const(pathsArray)) {
                paths.push_back(val.toString());
            }

            colourMap[colour] = std::move(paths);
        }

        spriteMap[type] = std::move(colourMap);
    }
    return spriteMap;
}

void TreeGraphicsItem::loadTreeSprites(std::vector<QString> pathArray)
{
    treeSprites.clear();
    for (const QString &path : pathArray) {
        QPixmap sprite(path);
        treeSprites.push_back(sprite);
    }
}

QString TreeGraphicsItem::treeTypeToString(TreeType type)
{
    switch (type) {
    case TreeType::TriangleSpruceTree: return "Triangle Spruce Tree";
    case TreeType::TinySpruceTree:     return "Tiny Spruce Tree";
    case TreeType::ThickSpruceTree:    return "Thick Spruce Tree";
    case TreeType::SpruceTrees:        return "Spruce Trees";
    case TreeType::SmallPineTree:      return "Small Pine Tree";
    case TreeType::SlimSpruceTree:     return "Slim Spruce Tree";
    case TreeType::PineTrees:          return "Pine Trees";
    case TreeType::PicoPineTree:       return "Pico Pine Tree";
    case TreeType::LargeSpruceTree:    return "Large Spruce Tree";
    case TreeType::BubblePineTree:     return "Bubble Pine Tree";
    }
}

TreeType TreeGraphicsItem::stringToTreeType(const QString &str)
{
    if (str == "Triangle Spruce Tree") return TreeType::TriangleSpruceTree;
    if (str == "Tiny Spruce Tree")     return TreeType::TinySpruceTree;
    if (str == "Thick Spruce Tree")    return TreeType::ThickSpruceTree;
    if (str == "Spruce Trees")         return TreeType::SpruceTrees;
    if (str == "Small Pine Tree")      return TreeType::SmallPineTree;
    if (str == "Slim Spruce Tree")     return TreeType::SlimSpruceTree;
    if (str == "Pine Trees")           return TreeType::PineTrees;
    if (str == "Pico Pine Tree")       return TreeType::PicoPineTree;
    if (str == "Large Spruce Tree")    return TreeType::LargeSpruceTree;
    if (str == "Bubble Pine Tree")     return TreeType::BubblePineTree;
    qWarning() << "Unknown TreeType:" << str;
    return TreeType::TriangleSpruceTree; // fallback
}

QString TreeGraphicsItem::treeColorToString(TreeColour color)
{
    switch (color) {
    case TreeColour::YELLOW:     return "YELLOW";
    case TreeColour::GREEN:      return "GREEN";
    case TreeColour::GREEN_TEAL: return "GREEN_TEAL";
    case TreeColour::TEAL:       return "TEAL";
    case TreeColour::COLD:       return "COLD";
    case TreeColour::NIGHT:      return "NIGHT";
    }
    return {};
}

TreeColour TreeGraphicsItem::stringToTreeColor(const QString &str)
{
    if (str == "YELLOW")     return TreeColour::YELLOW;
    if (str == "GREEN")      return TreeColour::GREEN;
    if (str == "GREEN_TEAL") return TreeColour::GREEN_TEAL;
    if (str == "TEAL")       return TreeColour::TEAL;
    if (str == "COLD")       return TreeColour::COLD;
    if (str == "NIGHT")      return TreeColour::NIGHT;
    qWarning() << "Unknown TreeColour:" << str;
    return TreeColour::GREEN; // fallback
}

void TreeGraphicsItem::updateToNextSprite()
{
    if (treeSprites.empty()) {
        return;
    }
    setPixmap(treeSprites[currentSpriteIndex]);
    currentSpriteIndex = (currentSpriteIndex + 1) % treeSprites.size();
}
