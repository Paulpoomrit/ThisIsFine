#ifndef TREEGRAPHICSITEM_H
#define TREEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QTimer>

enum class TreeType {
    TriangleSpruceTree,
    TinySpruceTree,
    ThickSpruceTree,
    SpruceTrees,
    SmallPineTree,
    SlimSpruceTree,
    PineTrees,
    PicoPineTree,
    LargeSpruceTree,
    BubblePineTree
};

enum class TreeColour {
    YELLOW,
    GREEN,
    GREEN_TEAL,
    TEAL,
    COLD,
    NIGHT
};


// typedef
// Sprite map is a map of maps
// - the outer map => TreeType + key (QMap)
// - the innter map => ThreeColour + key (vector of QStrings)
// - the std::vector<QString> is the file path to the sprites
using SpriteMap = QMap<TreeType, QMap<TreeColour, std::vector<QString>>>;

class TreeGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit TreeGraphicsItem(QGraphicsItem *parent = nullptr);
    std::vector<QString> getTreeFlipbookPath(TreeType, TreeColour);
    void animate(const int &fps);
    void stopAnimation();
private:
    std::vector<QPixmap> treeSprites;
    SpriteMap loadTreeSpritePaths(const QString &jsonPath);
    void loadTreeSprites(std::vector<QString>);

    QString treeTypeToString(TreeType type);
    TreeType stringToTreeType(const QString &str);

    QString treeColorToString(TreeColour color);
    TreeColour stringToTreeColor(const QString &str);

    QTimer *animTimer;
    void updateToNextSprite();
    int currentSpriteIndex;
};

#endif // TREEGRAPHICSITEM_H
