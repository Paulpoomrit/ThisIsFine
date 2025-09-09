#include "treegraphicsitem.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

TreeGraphicsItem::TreeGraphicsItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
}

SpriteMap TreeGraphicsItem::loadTreeSprites(const QString &jsonPath)
{
    SpriteMap spriteMap;
    QFile file(jsonPath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open JSON file:" << jsonPath;
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

    }
    return spriteMap;
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
