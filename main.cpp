#include "GameWindow.h"
#include "mainwindow.h"

#include <QApplication>
#include "mainmenu.h";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
