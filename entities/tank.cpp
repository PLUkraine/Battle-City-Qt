#include "tank.h"

Tank::Tank(Body *body, Renderer *renderer, Physics *physics, Health *health)
    : Entity()
{
    m_body = body;
    m_renderer = renderer;
    m_physics = physics;
    m_health = health;

    m_body->setParent(this);
    m_physics->setParent(this);
    m_health->setParent(this);

    m_health->setOwner(this);
    wire_renderer_to_body();
}

Tank::~Tank()
{
    unwire_renderer_from_body();
    dispose_of_renderer();
}

void Tank::update()
{
    m_physics->update(m_body);
}
