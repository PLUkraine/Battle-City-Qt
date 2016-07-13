#include "entitiesbag.h"
#include "game/board.h"

EntitiesBag::EntitiesBag(Tank *playerTank)
    : QObject(nullptr),
      m_playerTank(playerTank)

{
    connect(playerTank->health(), SIGNAL(died(Entity*)), this, SLOT(killPlayer()));
}

EntitiesBag::~EntitiesBag()
{
    for (Tank* tank: m_tanks)
        delete tank;
    for (Bullet* bullet : m_bullets)
        delete bullet;
    delete m_playerTank;
}

bool EntitiesBag::collidesWithTank(Body *body)
{
    return collisionWithTank(body) != nullptr;
}

Tank *EntitiesBag::collisionWithTank(Body *body)
{
    for (Tank* t : m_tanks)
        if (t->body()->collidesWith(body) && t->body() != body)
            return t;

    if (m_playerTank->body()->collidesWith(body)
            && m_playerTank->body() != body)
        return m_playerTank;
    else
        return nullptr;
}

void EntitiesBag::update(Actor *player, Board *board)
{
    player->makeMove(board, this, m_playerTank);
    updateTanks(board);
    updateBullets(board);
}

void EntitiesBag::addBullet(Bullet *b)
{
    m_bullets.insert(b);
}

void EntitiesBag::addTank(Tank *t)
{
    m_tanks.insert(t);
    connect(t->health(), SIGNAL(died(Entity*)), this, SLOT(deleteTank(Entity*)));
}

void EntitiesBag::deleteTank(Entity *tank)
{
    Tank* t = (Tank*)tank;
    disconnect(t->health(), SIGNAL(died(Entity*)), this, SLOT(deleteTank(Entity*)));
    m_tanks.erase(t);
    delete t;
    emit enemyDied();
}

void EntitiesBag::killPlayer()
{
    emit playerDied();
}

void EntitiesBag::updateBullets(Board *board)
{
    std::set<Bullet*> destroyedBullets;


    for (Bullet* b : m_bullets) {
        b->update();

        Tank* victim = collisionWithTank(b->body());
        QList<Tile*> tile_victims = board->detectCollision(b->body());

        if (!tile_victims.empty()){
            for (Tile* t : tile_victims) {
                t->health()->hit(b->damage());
            }
            destroyedBullets.insert(b);

        }
        else if (!board->inBoardBounds(b->body())) {
             destroyedBullets.insert(b);
        }
        else if (victim && victim != b->sender())
        {
            victim->health()->hit(b->damage());
            destroyedBullets.insert(b);
        }
    }
    for (Bullet* b: destroyedBullets){
        m_bullets.erase(b);
        delete b;
    }
}

void EntitiesBag::updateTanks(Board *)
{

}
