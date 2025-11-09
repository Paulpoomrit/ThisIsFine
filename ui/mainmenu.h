#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QtWidgets/qstackedwidget.h>
#include "gamemode.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    static GameMode doMainMenu(QStackedWidget *parent);

signals:
    void gameStarted(GameMode gameModeSelected);

private:
    Ui::MainMenu *ui;

    // QWidget interface
public:
    QSize sizeHint() const;

    // QWidget interface
public:
    int heightForWidth(int) const;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINMENU_H
