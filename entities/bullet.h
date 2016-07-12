#ifndef BULLET_H
#define BULLET_H

#include"entities/entity.h"
#include"entities/tank.h"

class Bullet : public Entity
{
    Q_OBJECT
public:
    Bullet(Body*body, Renderer*renderer, Physics* physics, Tank* sender, int damage);
    virtual ~Bullet();

    void update();

    Tank* sender() const;

    int damage() const;

protected:
    Tank* m_sender;
    int m_damage;
};

#endif // BULLET_H
