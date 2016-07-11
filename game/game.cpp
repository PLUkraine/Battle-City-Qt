#include "game.h"
#include<QPainter>

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    QImage* image = new QImage(":/sprites/wall.png", "PNG");

    Body* body = new Body(20, 30, 40, 40, 2);
    Renderer* ren = new Renderer(image, this);

    Body* body2 = new Body(60, 30, 40, 40, 2);
    Renderer* ren2 = new Renderer(image, this);

    tile = new Tile(body, ren, true);
    Tile* tile2 = new Tile(body2, ren2, false);

    qDebug() << tile->body()->collidesWith(tile2->body());
}

void Game::paint(QPainter *)
{

}

void Game::registerInQML()
{
    qmlRegisterType<Game>("BattleCity", 1, 0, "Game");
}
