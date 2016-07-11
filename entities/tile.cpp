#include "tile.h"

Tile::Tile(Body *body, Renderer *renderer, bool is_solid) : QObject(nullptr),
    m_body(body),
    m_renderer(renderer),
    m_is_solid(is_solid)
{
    m_body->setParent(this);
    // renderer and body should be synchronized
    m_renderer->setPosition(m_body->pos());
    m_renderer->setWidth(m_body->width());
    m_renderer->setHeight(m_body->height());
    m_renderer->update();

    connect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));
}

Tile::~Tile()
{
    disconnect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));

    m_renderer->setParent(nullptr);
    delete m_renderer;
}

Body *Tile::body() const
{
    return m_body;
}
