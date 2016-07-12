#include "bullet.h"

Bullet::Bullet(Body *body, Renderer *renderer, Physics *physics, Tank* sender)
    : Entity(),
      m_sender(sender)
{
    m_body = body;
    m_renderer = renderer;
    m_physics = physics;

    m_body->setParent(this);
    m_physics->setParent(this);

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

Tank *Bullet::sender() const
{
    return m_sender;
}
