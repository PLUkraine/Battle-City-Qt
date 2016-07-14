#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H
#include "entitiesfactory.h"
#include"entities/explosion.h"

class ExplosionFactory : public EntitiesFactory
{
public:
    ExplosionFactory(Game* game);
    Explosion* createExplosion(qreal x, qreal y);
};

#endif // EXPLOSIONFACTORY_H
