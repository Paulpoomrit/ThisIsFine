#ifndef TREEGRAPHICSITEM_H
#define TREEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>

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

class TreeGraphicsItem : public QGraphicsPixmapItem
{
public:
    explicit TreeGraphicsItem(QGraphicsItem *parent = nullptr);
    std::vector<QString> getTreeFlipbookPath(TreeType, TreeColour);
private:
    SpriteMap treeSpriteMap;
    void loadTreeSprites();
};

#endif // TREEGRAPHICSITEM_H
