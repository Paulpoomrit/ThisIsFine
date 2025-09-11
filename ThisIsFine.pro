QT       += core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    flame.cpp \
    gamescene.cpp \
    gamewindow.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    retrobutton.cpp \
    soundcue.cpp \
    tile.cpp \
    tilegraphicsitem.cpp \
    tilelogic.cpp \
    treegraphicsitem.cpp \

HEADERS += \
    flame.h \
    gamemode.h \
    gamescene.h \
    gamewindow.h \
    mainmenu.h \
    mainwindow.h \
    retrobutton.h \
    soundcue.h \
    tile.h \
    tilegraphicsitem.h \
    tilelogic.h \
    tilestates.h \
    treegraphicsitem.h

FORMS += \
    gamewindow.ui \
    mainmenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    flameSprites.json \
    treeSprites.json
