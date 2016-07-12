#include "game.h"
#include<QPainter>
#include<QDebug>

const qreal TILE_SIZE = 3;
const qreal BULLET_SIZE = 1;
const qreal TANK_SIZE = 3;
const qreal TANK_SPEED = 0.5;

const qreal WINDOW_W = 800;
const qreal WINDOW_H = 600;

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    tileSprites[0] = QImage(":/sprites/air.png");
    tileSprites[1] = QImage(":/sprites/wall.png");
    tankSprite = QImage(":/sprites/tank.png");

    board = new Board(WINDOW_W, WINDOW_H);
    TileBuilder builder(this, tileSprites);
    builder.setSize(TILE_SIZE);
    board->loadBoard("level.json", &builder);
    QSizeF ratio = board->getTileRatio();

    player = new Player();

    playerTank = new Tank(
                new Body(2*TILE_SIZE, 2*TILE_SIZE ,TANK_SIZE, TANK_SIZE),
                new Renderer(&tankSprite, ratio.width(), ratio.height(), this),
                new Physics(TANK_SPEED, Direction::DOWN)
                );

    qDebug() << playerTank->body()->boundingRect();
    qDebug() << board->getLeftCoord(playerTank->body());


    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer.start(1000/14);
}

Game::~Game()
{
    delete board;
    delete player;
}

void Game::paint(QPainter *)
{

}

void Game::keyPressEvent(QKeyEvent *event)
{

    if (!event->isAutoRepeat())
    {
        //qDebug() << "Set key";
        player->setKey((Qt::Key)event->key(), true);
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {

        player->setKey((Qt::Key)event->key(), false);
    }
}

void Game::registerInQML()
{
    qmlRegisterType<Game>("BattleCity", 1, 0, "Game");
}

void Game::updateGame()
{
    player->makeMove(board, playerTank);
//    qreal x = board->getLeftCoord(playerTank->body());
//    playerTank->body()->setPosition(x, playerTank->body()->y());
}
