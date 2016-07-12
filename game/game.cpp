#include "game.h"
#include<QPainter>
#include<QDebug>

#include "game/board.h"

const int TILE_SIZE = 4;
const int BULLET_SIZE = 1;
const int TANK_SIZE = 4;


Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    tileSprites[0] = QImage(":/sprites/air.png");
    tileSprites[1] = QImage(":/sprites/wall.png");

    Board* b = new Board(160,120);
    TileBuilder builder(this, tileSprites);
    builder.setSize(TILE_SIZE);


    b->loadBoard("level.json", &builder);

//    Body *bod = new Body(0,0, 20, 20);
//    qDebug() << b->intersectsTiles(bod);
}

void Game::paint(QPainter *)
{

}

void Game::registerInQML()
{
    qmlRegisterType<Game>("BattleCity", 1, 0, "Game");
}
