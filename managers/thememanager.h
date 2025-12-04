#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QApplication>


class ThemeManager
{
public:
    ThemeManager();
    static void doTheme(const QApplication& app);
};

#endif // THEMEMANAGER_H
