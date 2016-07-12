#ifndef ENTITIESBAG_H
#define ENTITIESBAG_H

#include <set>

#include "entities/bullet.h"
#include "entities/tank.h"
#include "actors/player.h"

class EntitiesBag
{
public:
    EntitiesBag(Tank* playerTank);
    ~EntitiesBag();

    bool collidesWith(Body* body);

    void update(Actor* player, Board* board);

public slots:
    void addBullet(Bullet*);
    void addTank(Tank*);
private:
    void updateBullets();
    void updateTanks();

    std::set<Bullet*> m_bullets;
    std::set<Tank*> m_tanks;
    Tank* m_playerTank;
};

#endif // ENTITIESBAG_H
