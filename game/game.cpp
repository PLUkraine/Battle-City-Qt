#include "game.h"
#include<QPainter>
#include<QDebug>
#include "utils/resoursecontainer.h"
#include "game/entitiesbag.h"

const qreal WINDOW_W = 400;
const qreal WINDOW_H = 300;

Game::Game(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    // create board
    board = new Board(WINDOW_W, WINDOW_H);
    TileBuilder builder(this, ResBag::get().tilesSptites());
    builder.setSize(ResBag::get().tileSize());
    board->loadBoard("level.json", &builder);
    QSizeF ratio = board->getTileRatio();

    // create player
    player = new Player();
    Tank* playerTank = new Tank(
                new Body(3*ResBag::get().tileSize(), 3*ResBag::get().tileSize(),
                         ResBag::get().tankSize(), ResBag::get().tankSize(), Direction::DOWN),
                new Renderer(ResBag::get().tankSprite(), ratio.width(), ratio.height(), this),
                new Physics(ResBag::get().tankSpeed())
                );

    // create entities bag
    bag = new EntitiesBag(playerTank);
    bag->addTank(new Tank(
                     new Body(3*ResBag::get().tileSize(), 5*ResBag::get().tileSize(),
                              ResBag::get().tankSize(), ResBag::get().tankSize(), Direction::DOWN),
                     new Renderer(ResBag::get().tankSprite(), ratio.width(), ratio.height(), this),
                     new Physics(ResBag::get().tankSpeed())
                     ));

    // start game
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer.start(1000/14);
}

Game::~Game()
{
    delete board;
    delete player;
    delete bag;
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
    //player->makeMove(board,  playerTank);
    bag->update(player, board);
}


//void Game::updateBullets()
//{
//    std::set<Bullet*> destroyedBullets;
//    for (Bullet* b : bullets) {
//        b->update();
//        if (board->collidesWithBoard(b->body()) || !board->inBoardBounds(b->body()))
//            destroyedBullets.insert(b);
//    }
//    for (Bullet* b: destroyedBullets){
//        bullets.erase(b);
//        delete b;
//    }
//}
