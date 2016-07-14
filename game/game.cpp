#include<QPainter>
#include<QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>

#include "game.h"
#include "utils/resoursecontainer.h"
#include "game/entitiesbag.h"

const qreal WINDOW_W = 690;
const qreal WINDOW_H = 690;

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      board(nullptr),
      player(nullptr),
      bag(nullptr)
{
    loadLevel(":/levels/level1.json");

    // start game
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer.start(1000/30);
}

Game::~Game()
{
    cleanup();
}

void Game::paint(QPainter *)
{
}

QSizeF Game::getRatioFromBoard() const
{
    return board->getTileRatio();
}

void Game::keyPressEvent(QKeyEvent *event)
{

    if (!event->isAutoRepeat())
    {
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
    bag->update(player, board);
}

void Game::cleanup()
{
    if (board)
        delete board;
    if (bag)
        delete bag;
    if (player)
        delete player;
}

bool Game::loadLevel(QString filename)
{
    QFile inFile(filename);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = inFile.readAll();
    inFile.close();

    QJsonParseError er;
    QJsonObject root = QJsonDocument::fromJson(val, &er).object();
    // if error occurred, abort level creation
    if (er.error != QJsonParseError::NoError) {
        return false;
    }

    // clean before any changes
    cleanup();

    // create board
    TileBuilder* builder = new TileBuilder(this);
    board = new Board(WINDOW_W, WINDOW_H, builder);
    board->loadBoard(root);
    QSizeF ratio = board->getTileRatio();

    // create player
    int player_x = root["player"].toObject()["x"].toInt();
    int player_y = root["player"].toObject()["y"].toInt();
    player = new Player();
    Tank* playerTank = new Tank(
                new Body(player_x*ResBag::get().tileSize(), player_y*ResBag::get().tileSize(),
                         ResBag::get().tankSize(), ResBag::get().tankSize(), Direction::DOWN),
                new DirectionRenderer(ResBag::get().tankSprite(), ratio.width(), ratio.height(), this),
                new Physics(ResBag::get().tankSpeed()),
                new Health(ResBag::get().tankHealth()),
                new StandartWeapon(this)
                );

    // create entities bag
    bag = new EntitiesBag(playerTank);
//    bag->addTank(new Tank(
//                     new Body(3*ResBag::get().tileSize(), 5*ResBag::get().tileSize(),
//                              ResBag::get().tankSize(), ResBag::get().tankSize(), Direction::DOWN),
//                     new DirectionRenderer(ResBag::get().tankSprite(), ratio.width(), ratio.height(), this),
//                     new Physics(ResBag::get().tankSpeed()),
//                     new Health(ResBag::get().tankHealth()),
//                     new StandartWeapon(this)
//                     ));
//    bag->addBullet(new Bullet(
//                       new Body(3*ResBag::get().tileSize(), 4*ResBag::get().tileSize(),
//                                ResBag::get().bulletSize(), ResBag::get().bulletSize(), Direction::RIGHT),
//                       new StaticRenderer(ResBag::get().bulletSprite(), ratio.width(), ratio.height(), this),
//                       new Physics(ResBag::get().bulletSpeed()),
//                       nullptr,
//                       ResBag::get().bulletDamage()
//                       ));
    return true;
}


