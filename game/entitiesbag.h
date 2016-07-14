#ifndef ENTITIESBAG_H
#define ENTITIESBAG_H

#include <set>
#include <map>

#include "entities/bullet.h"
#include "entities/tank.h"
#include "entities/explosion.h"
#include "actors/player.h"
#include "actors/dummyai.h"

class TankFactory;
class ExplosionFactory;
class EntitiesBag : public QObject
{
    Q_OBJECT
public:
    EntitiesBag(Tank* playerTank, TankFactory* tankFactory, ExplosionFactory* explFactory, int maxTanks, int tanksToSpawn, Game *game);
    virtual ~EntitiesBag();

    bool collidesWithTank(Body* body);
    Tank* collisionWithTank(Body* body);

    void update(Actor* player, Board* board);

    int tanksCount() const;
    int tanksLeft() const;
    Tank* playerTank() const;

signals:
    void playerDied();
    void enemyDied();
    void allEnemiesDied();
    void allEnemiesSpawned();
public slots:
    void addExplosion(Explosion*expl);
    void addBullet(Bullet*);
    void spawnTank(Board *board);
    void spawnExplosion(Body* body);
private slots:
    void deleteTank(Entity*);
    void killPlayer();
    void addTank(Tank*);
private:
    void updateBullets(Board *board);
    void updateTanks(Board *board);
    void updateExplosions();

    std::set<Bullet*> m_bullets;
    std::set<Tank*> m_tanks;
    std::set<Explosion*> m_explosions;
    std::map<Tank*, DummyAI*> m_ai;
    Tank* m_playerTank;
    TankFactory* m_tankFactory;
    ExplosionFactory* m_explosionFactory;

    // max ammount of tanks on board
    int m_max_tanks;
    int m_tanks_left;
};

#endif // ENTITIESBAG_H
