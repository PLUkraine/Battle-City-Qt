#include "tank.h"

Tank::Tank(Body *body, Renderer *renderer, Physics *physics, Health *health, Weapon* weapon)
    : Entity()
{
    m_body = body;
    m_renderer = renderer;
    m_physics = physics;
    m_health = health;
    m_weapon = weapon;

    m_body->setParent(this);
    m_physics->setParent(this);
    m_health->setParent(this);
    m_weapon->setParent(this);

    wire_health();
    wire_weapon();
    wire_renderer_to_body();
}

Tank::~Tank()
{
    unwire_renderer_from_body();
    dispose_of_renderer();
}

void Tank::update()
{
    Entity::update();
    m_physics->update(m_body);
}
