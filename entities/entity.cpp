#include "entity.h"

Entity::Entity() : QObject(nullptr),
    m_renderer(nullptr),
    m_body(nullptr)
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

    connect(m_body, SIGNAL(positionChanged(int,int)), m_renderer, SLOT(onUpdatePos(int,int)));
    connect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdateSize(int,int)));
}

void Entity::unwire_renderer_from_body()
{
    disconnect(m_body, SIGNAL(positionChanged(int,int)), m_renderer, SLOT(onUpdatePos(int,int)));
    disconnect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdateSize(int,int)));
}

void Entity::dispose_of_renderer()
{
    m_renderer->setParent(nullptr);
    delete m_renderer;
}

Physics *Entity::physics() const
{
    return m_physics;
}
