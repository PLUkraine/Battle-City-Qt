#include<QPainter>
#include<QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>
#include <random>

#include "game.h"
#include "utils/resoursecontainer.h"
#include "game/entitiesbag.h"
#include"game/board.h"
#include "factories/tankfactory.h"

const qreal WINDOW_W = 690;
const qreal WINDOW_H = 690;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist(0.0,1.0);

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      board(nullptr),
      player(nullptr),
      bag(nullptr)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    createAndStartGame(":/levels/level1.json");
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

    if (!event->isAutoRepeat()) {
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

void Game::createAndStartGame(QString level)
{
    loadLevel(level);
    timer.setSingleShot(false);
    timer.start(ResBag::get().timerInterval());
}


void Game::pauseOrResumeGame()
{
    if (timer.isActive())
        timer.stop();
    else
        timer.start();
}

void Game::stopGame()
{
    timer.stop();
}

void Game::updateGame()
{
    bag->update(player, board);
    if (dist(gen)< 0.1)
        bag->spawnTank(board);
}

void Game::activateGameOver()
{
    if (timer.isActive()) {
        qDebug() << "Game over";
        stopGame();
        emit gameOver();
    }
}

void Game::activateVictory()
{
    stopGame();
    emit victory();
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

    // clean before making any changes
    cleanup();

    // create board
    TileBuilder* builder = new TileBuilder(this);
    board = new Board(WINDOW_W, WINDOW_H, builder);
    board->loadBoard(root);
    connect(board, SIGNAL(baseDestroyed()), this, SLOT(activateGameOver()), Qt::DirectConnection);
    QSizeF ratio = board->getTileRatio();

    // create player
    int player_x = root["player"].toObject()["x"].toInt()*ResBag::get().tileSize();
    int player_y = root["player"].toObject()["y"].toInt()*ResBag::get().tileSize();
    player = new Player();
    TankFactory* tankFactory = new TankFactory(this);
    tankFactory->setRatio(ratio);
    Tank* playerTank = tankFactory->createPlayerTank(player_x, player_y);

    // create entities bag
    QJsonObject game = root["game"].toObject();
    int maxTanks = game["maxTanks"].toInt();
    int tanksToSpawn = game["tanks"].toInt();
    int startTanksCount = game["startTanksCount"].toInt();
    bag = new EntitiesBag(playerTank, tankFactory, maxTanks, tanksToSpawn);
    connect(bag, SIGNAL(playerDied()), this, SLOT(activateGameOver()));
    connect(bag, SIGNAL(allEnemiesDied()), this, SLOT(activateVictory()));

    for (int i=0; i<startTanksCount; ++i)
        bag->spawnTank(board);

    return true;
}


