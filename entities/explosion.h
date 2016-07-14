#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "entities/entity.h"

class Explosion : public Entity
{
    Q_OBJECT
public:
    Explosion(Renderer* renderer, Body* body, int timeToLive);
    virtual ~Explosion();
    bool mustDie() const;

protected:
    int m_time_to_live;
};

#endif // EXPLOSION_H
