#ifndef FLAME_H
#define FLAME_H

#include <QGraphicsPixmapItem>

enum class FlameType {
    FLAME_1,
    FLAME_2,
    FLAME_9,
    FLAME_11,
    FLAME_12
};

using FlameSpriteMap = QMap<FlameType, std::vector<QString>>;

class Flame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Flame(QGraphicsItem *parent = nullptr);
    void animate(const int &fps);
private:
    FlameSpriteMap loadFlameSpritePaths(const QString& jsonPath);
    std::vector<QPixmap> flameSprites;

    QString flameTypeToString(FlameType type);
    FlameType stringToFlameType(const QString &str);
    FlameType getRandomFlameType() const;
    void loadFlameSprites(const std::vector<QString> &pathArray);

    QTimer *animTimer;

    void updateToNextSprite();
    int currentSpriteIndex;
};
#endif // FLAME_H
