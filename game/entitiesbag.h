#ifndef ENTITIESBAG_H
#define ENTITIESBAG_H

#include <set>
#include <map>

#include "entities/bullet.h"
#include "entities/tank.h"
#include "actors/player.h"
#include "actors/dummyai.h"

class TankFactory;
class EntitiesBag : public QObject
{
    Q_OBJECT
public:
    EntitiesBag(Tank* playerTank, TankFactory* tankFactory, int maxTanks, int tanksToSpawn, Game *game);
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
    void addBullet(Bullet*);
    void spawnTank(Board *board);
private slots:
    void deleteTank(Entity*);
    void killPlayer();
    void addTank(Tank*);
private:

    void updateBullets(Board *board);
    void updateTanks(Board *board);

    std::set<Bullet*> m_bullets;
    std::set<Tank*> m_tanks;
    std::map<Tank*, DummyAI*> m_ai;
    Tank* m_playerTank;
    TankFactory* m_tankFactory;

    // max ammount of tanks on board
    int m_max_tanks;
    int m_tanks_left;
};

#endif // ENTITIESBAG_H
