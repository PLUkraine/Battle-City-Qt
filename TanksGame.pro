TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    game/game.cpp \
    components/renderer.cpp \
    components/body.cpp \
    entities/tile.cpp \
    game/board.cpp \
    factories/tilebuilder.cpp \
    components/physics.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -Wall

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    game/game.h \
    components/renderer.h \
    components/body.h \
    entities/tile.h \
    game/board.h \
    factories/tilebuilder.h \
    components/physics.h
