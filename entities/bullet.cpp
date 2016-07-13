#include "bullet.h"

Bullet::Bullet(Body *body, Renderer *renderer, Physics *physics, Entity *sender, int damage)
    : Entity(),
      m_sender(sender),
      m_damage(damage)
{
    m_body = body;
    m_renderer = renderer;
    m_physics = physics;

    m_body->setParent(this);
    m_physics->setParent(this);
    m_physics->setSpeed(m_physics->max_speed());

    wire_renderer_to_body();
}

Bullet::~Bullet()
{
    unwire_renderer_from_body();
    dispose_of_renderer();
}

void Bullet::update()
{
    physics()->update(body());
}

Entity *Bullet::sender() const
{
    return m_sender;
}

int Bullet::damage() const
{
    return m_damage;
}
