#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include"game/game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Game::registerInQML();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
