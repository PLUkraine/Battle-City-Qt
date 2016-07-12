#ifndef BULLET_H
#define BULLET_H

#include"entities/entity.h"
#include"entities/tank.h"

class Bullet : public Entity
{
    Q_OBJECT
public:
    Bullet(Body*body, Renderer*renderer, Physics* physics, Tank* sender);
    virtual ~Bullet();

    void update();

    Tank* sender() const;

protected:
    Tank* m_sender;
};

#endif // BULLET_H
