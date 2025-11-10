QT       += core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamescene.cpp \
    graphicsitems/flame.cpp \
    graphicsitems/tilegraphicsitem.cpp \
    graphicsitems/treegraphicsitem.cpp \
    graphicsitems/truckgraphicsitem.cpp \
    logicitems/firetruck.cpp \
    logicitems/tile.cpp \
    logicitems/tilelogic.cpp \
    main.cpp \
    managers/levelmanager.cpp \
    managers/thememanager.cpp \
    sound/soundcue.cpp \
    ui/gamewindow.cpp \
    ui/mainmenu.cpp \
    ui/retrobutton.cpp

HEADERS += \
    gamemode.h \
    gamescene.h \
    graphicsitems/flame.h \
    graphicsitems/spawnmode.h \
    graphicsitems/tilegraphicsitem.h \
    graphicsitems/treegraphicsitem.h \
    graphicsitems/truckgraphicsitem.h \
    logicitems/firetruck.h \
    logicitems/tile.h \
    logicitems/tilelogic.h \
    logicitems/tilestates.h \
    managers/configinfo.h \
    managers/endgamestates.h \
    managers/levelmanager.h \
    managers/thememanager.h \
    sound/soundcue.h \
    ui/gamewindow.h \
    ui/mainmenu.h \
    ui/retrobutton.h

FORMS += \
    ui/gamewindow.ui \
    ui/mainmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    flameSprites.json \
    treeSprites.json
