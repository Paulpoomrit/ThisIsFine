#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include <gamescene.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    GameScene getScene();

private:
    Ui::GameWindow *ui;
    GameScene *scene;
    QSize calculateTileSize(int numRow, int numCol) const;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // GAMEWINDOW_H
