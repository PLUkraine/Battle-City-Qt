#ifndef TANKFACTORY_H
#define TANKFACTORY_H
#include "entitiesfactory.h"
#include "utils/resoursecontainer.h"
#include "entities/tank.h"

class TankFactory : public EntitiesFactory
{
public:
    TankFactory(Game* game);

    Tank *createTank(qreal x, qreal y);
    Tank *createPlayerTank(qreal x, qreal y);
};

#endif // TANKFACTORY_H
