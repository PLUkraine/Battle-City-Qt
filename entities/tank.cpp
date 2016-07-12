#include "tank.h"

Tank::Tank(Body *body, Renderer *renderer, Physics *physics)
    : Entity()
{
    m_body = body;
    m_renderer = renderer;
    m_physics = physics;

    m_body->setParent(this);
    m_physics->setParent(this);

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
