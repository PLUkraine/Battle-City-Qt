#ifndef ENTITIESBAG_H
#define ENTITIESBAG_H

#include <set>
#include <map>

#include "entities/bullet.h"
#include "entities/tank.h"
#include "actors/player.h"
#include "actors/dummyai.h"

class EntitiesBag : public QObject
{
    Q_OBJECT
public:
    EntitiesBag(Tank* playerTank, int maxTanks, int tanksToSpawn);
    virtual ~EntitiesBag();

    bool collidesWithTank(Body* body);
    Tank* collisionWithTank(Body* body);

    void update(Actor* player, Board* board);

    int tanksCount() const;


signals:
    void playerDied();
    void enemyDied();
    void allEnemiesDied();

public slots:
    void addBullet(Bullet*);
    void addTank(Tank*);
    void spawnTank();
private slots:
    void deleteTank(Entity*);
    void killPlayer();
private:

    void updateBullets(Board *board);
    void updateTanks(Board *board);

    std::set<Bullet*> m_bullets;
    std::set<Tank*> m_tanks;
    std::map<Tank*, DummyAI*> m_ai;
    Tank* m_playerTank;

    // max ammount of tanks on board
    int m_max_tanks;
    int m_tanks_left;
};

#endif // ENTITIESBAG_H
