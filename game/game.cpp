#include "game.h"
#include<QPainter>
#include<QDebug>

#include "game/board.h"
Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    tileSprites[0] = QImage(":/sprites/air.png");
    tileSprites[1] = QImage(":/sprites/wall.png");

    Board* b = new Board(160,120);
    b->loadBoard("level.json", new TileBuilder(this, tileSprites));

    Body *bod = new Body(0,0, 20, 20);
    qDebug() << b->intersectsTiles(bod);
}

void Game::paint(QPainter *)
{

}

void Game::registerInQML()
{
    qmlRegisterType<Game>("BattleCity", 1, 0, "Game");
}
