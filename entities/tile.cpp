#include "tile.h"

Tile::Tile(Body *body, Renderer *renderer, bool is_solid, QObject *parent) : QObject(parent),
    m_body(body),
    m_renderer(renderer),
    m_is_solid(is_solid)
{
    m_body->setParent(this);

    // renderer and body should be synchronized
    m_renderer->setPosition(m_body->pos());
    m_renderer->setWidth(m_body->width());
    m_renderer->setHeight(m_body->height());

    connect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));
    connect(m_body, SIGNAL(sizeChanged(qreal,qreal)), m_renderer, SLOT(onUpdateSize(qreal,qreal)));
}

Tile::~Tile()
{
    qDebug() << "Destructor";
    disconnect(m_body, SIGNAL(positionChanged(qreal,qreal)), m_renderer, SLOT(onUpdatePos(qreal,qreal)));
    disconnect(m_body, SIGNAL(sizeChanged(qreal,qreal)), m_renderer, SLOT(onUpdateSize(qreal,qreal)));

    m_renderer->setParent(nullptr);
    delete m_renderer;
}

Body *Tile::body() const
{
    return m_body;
}
