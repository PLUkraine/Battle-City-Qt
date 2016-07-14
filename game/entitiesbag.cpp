#include "entitiesbag.h"
#include "game/board.h"
#include "factories/tankfactory.h"
#include "factories/explosionfactory.h"
#include <algorithm>

bool xor_(bool x, bool y) {
    return (x && !y) || (!x && y);
}

EntitiesBag::EntitiesBag(Tank *playerTank, TankFactory* tankFactory, ExplosionFactory *explFactory, int maxTanks, int tanksToSpawn, Game* game)
    : QObject(nullptr),
      m_playerTank(playerTank),
      m_tankFactory(tankFactory),
      m_explosionFactory(explFactory),
      m_max_tanks(maxTanks),
      m_tanks_left(tanksToSpawn)

{
    connect(playerTank->health(), SIGNAL(died(Entity*)), this, SLOT(killPlayer()));
    connect(playerTank->health(), SIGNAL(wasHit(int)), game, SLOT(playerHealthChange(int)), Qt::DirectConnection);
}

EntitiesBag::~EntitiesBag()
{
    for (Tank* tank: m_tanks)
        delete tank;
    for (Bullet* bullet : m_bullets)
        delete bullet;
    for (Explosion* explosion: m_explosions)
        delete explosion;
    delete m_playerTank;
    delete m_tankFactory;
    delete m_explosionFactory;
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
    updateExplosions();
    player->makeMove(board, this, m_playerTank);
    updateTanks(board);
    updateBullets(board);
}

int EntitiesBag::tanksCount() const
{
    return m_tanks.size();
}

int EntitiesBag::tanksLeft() const
{
    return m_tanks_left;
}

Tank *EntitiesBag::playerTank() const
{
    return m_playerTank;
}

void EntitiesBag::addExplosion(Explosion * expl)
{
    m_explosions.insert(expl);
}

void EntitiesBag::addBullet(Bullet *b)
{
    m_bullets.insert(b);
}

void EntitiesBag::addTank(Tank *t)
{
    m_tanks.insert(t);
    connect(t->health(), SIGNAL(died(Entity*)), this, SLOT(deleteTank(Entity*)));
    m_ai[t] = new DummyAI();
}

void EntitiesBag::spawnTank(Board* board)
{
    if (m_tanks_left > 0 && m_tanks.size() < (uint)m_max_tanks) {
        QList<const Tile *> freeTiles = board->spawnableTiles();
        std::random_shuffle(freeTiles.begin(), freeTiles.end());
        Tank * tank = m_tankFactory->createTank(0,0);
        bool success = false;

        for (const Tile* t : freeTiles) {
            tank->body()->setPosition(t->body()->x(), t->body()->y());
            // check if does not collide with anyone
            if (!board->collidesWithBoard(tank->body())
                    && !collidesWithTank(tank->body())
                    && board->inBoardBounds(tank->body()))
            {
                success = true;
                break;
            }
        }

        if (success) {
            addTank(tank);
            m_tanks_left--;
            if (m_tanks_left == 0)
                emit allEnemiesSpawned();
        } else  {
            delete tank;
        }
    }
}

void EntitiesBag::spawnExplosion(Body *body)
{
    m_explosionFactory->setSize(QSizeF(body->width(), body->height()));
    addExplosion(m_explosionFactory->createExplosion(body->x(), body->y()));
}

void EntitiesBag::deleteTank(Entity *tank)
{
    Tank* t = (Tank*)tank;
    disconnect(t->health(), SIGNAL(died(Entity*)), this, SLOT(deleteTank(Entity*)));

    spawnExplosion(t->body());

    m_tanks.erase(t);
    delete m_ai[t];
    m_ai.erase(t);
    delete t;
    emit enemyDied();
    if (m_tanks_left == 0 && m_tanks.empty()) {
        emit allEnemiesDied();
    }
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
        else if (victim &&
                 xor_(victim==m_playerTank, b->sender()==m_playerTank))
        {
            victim->health()->hit(b->damage());
            destroyedBullets.insert(b);
        }
    }
    for (Bullet* b: destroyedBullets){
        // spawnExplosion(b->body());
        m_bullets.erase(b);
        delete b;
    }
}

void EntitiesBag::updateTanks(Board *b)
{
    for (Tank *t: m_tanks) {
        m_ai[t]->makeMove(b, this, t);
    }
}

void EntitiesBag::updateExplosions()
{
    std::set<Explosion*> destroyedExplosions;
    for (Explosion *e: m_explosions) {
        e->update();
        if (e->mustDie())
            destroyedExplosions.insert(e);
    }

    for (Explosion *e: destroyedExplosions) {
        m_explosions.erase(e);
        delete e;
    }
}
