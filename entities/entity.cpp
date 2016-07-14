#include "entity.h"

Entity::Entity() : QObject(nullptr),
    m_renderer(nullptr),
    m_body(nullptr),
    m_physics(nullptr),
    m_health(nullptr),
    m_weapon(nullptr),
    m_ticks_lived(0)
{
}

Renderer *Entity::renderer() const
{
    return m_renderer;
}

Body *Entity::body() const
{
    return m_body;
}

void Entity::wire_renderer_to_body()
{
    m_renderer->onUpdatePos(m_body->x(), m_body->y());
    m_renderer->onUpdateSize(m_body->width(), m_body->height());
    m_renderer->onUpdateDirection(m_body->direction());
    m_renderer->onUpdateTime(m_ticks_lived);

    connect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));
    connect(m_body, SIGNAL(sizeChanged(qreal,qreal)), m_renderer, SLOT(onUpdateSize(qreal,qreal)));
    connect(m_body, SIGNAL(directionChanged(Direction)), m_renderer, SLOT(onUpdateDirection(Direction)));
}

void Entity::unwire_renderer_from_body()
{
    disconnect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));
    disconnect(m_body, SIGNAL(sizeChanged(qreal,qreal)), m_renderer, SLOT(onUpdateSize(qreal,qreal)));
    disconnect(m_body, SIGNAL(directionChanged(Direction)), m_renderer, SLOT(onUpdateDirection(Direction)));
}

void Entity::wire_health()
{
    m_health->setOwner(this);
}

void Entity::wire_weapon()
{
    m_weapon->setOwner(this);
}

void Entity::dispose_of_renderer()
{
    m_renderer->setParent(nullptr);
    delete m_renderer;
}

int Entity::ticks_lived() const
{
    return m_ticks_lived;
}

Weapon *Entity::weapon() const
{
    return m_weapon;
}

Health *Entity::health() const
{
    return m_health;
}

Physics *Entity::physics() const
{
    return m_physics;
}

void Entity::update()
{
    ++m_ticks_lived;
    if (m_weapon)
    {
        m_weapon->update();
    }
    if (m_renderer) {
        m_renderer->onUpdateTime(m_ticks_lived);
    }
}
