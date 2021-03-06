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
    components/physics.cpp \
    entities/entity.cpp \
    entities/tank.cpp \
    actors/actor.cpp \
    actors/player.cpp \
    entities/bullet.cpp \
    game/entitiesbag.cpp \
    utils/resoursecontainer.cpp \
    factories/entitiesfactory.cpp \
    components/health.cpp \
    components/weapon.cpp \
    components/component.cpp \
    actors/dummyai.cpp \
    factories/tankfactory.cpp \
    entities/explosion.cpp \
    factories/explosionfactory.cpp

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
    components/physics.h \
    entities/entity.h \
    entities/tank.h \
    actors/actor.h \
    actors/player.h \
    entities/bullet.h \
    game/entitiesbag.h \
    utils/resoursecontainer.h \
    factories/entitiesfactory.h \
    components/health.h \
    components/weapon.h \
    components/component.h \
    actors/dummyai.h \
    factories/tankfactory.h \
    entities/explosion.h \
    factories/explosionfactory.h
