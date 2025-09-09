#include "treegraphicsitem.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

TreeGraphicsItem::TreeGraphicsItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
}
