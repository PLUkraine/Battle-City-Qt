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
    EntitiesBag(Tank* playerTank);
    virtual ~EntitiesBag();

    bool collidesWithTank(Body* body);
    Tank* collisionWithTank(Body* body);

    void update(Actor* player, Board* board);


signals:
    void playerDied();
    void enemyDied();

public slots:
    void addBullet(Bullet*);
    void addTank(Tank*);
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
};

#endif // ENTITIESBAG_H
