QT       += core gui
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    all_enemies.cpp \
    block.cpp \
    boss.cpp \
    cat.cpp \
    enemy.cpp \
    human.cpp \
    main.cpp \
    music.cpp \
    valeryana.cpp \
    widget.cpp

HEADERS += \
    all_enemies.h \
    block.h \
    boss.h \
    cat.h \
    enemy.h \
    human.h \
    lvl.h \
    lvl.h \
    music.h \
    valeryana.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
