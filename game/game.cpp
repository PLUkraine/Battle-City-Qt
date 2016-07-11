#include "game.h"
#include<QPainter>

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}

void Game::paint(QPainter *painter)
{
    painter->fillRect(QRect(0,0,40,50), QBrush(QColor(255,0,0)));
}

void Game::registerInQML()
{
    qmlRegisterType<Game>("BattleCity", 1, 0, "Game");
}
