#include "tile.h"

Tile::Tile(Body *body, Renderer *renderer, bool is_solid, QObject *parent) : QObject(parent),
    m_body(body),
    m_renderer(renderer),
    m_is_solid(is_solid)
{
    m_body->setParent(this);

    // renderer and body should be synchronized
    m_renderer->onUpdatePos(m_body->x(), m_body->y());
    m_renderer->onUpdateSize(m_body->width(), m_body->height());

    connect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdatePos(int,int)));
    connect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdateSize(int,int)));
}

Tile::~Tile()
{
//    qDebug() << "Destructor";
    disconnect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdatePos(int,int)));
    disconnect(m_body, SIGNAL(sizeChanged(int,int)), m_renderer, SLOT(onUpdateSize(int,int)));

    m_renderer->setParent(nullptr);
    delete m_renderer;
}

Body *Tile::body() const
{
    return m_body;
}

bool Tile::is_solid() const
{
    return m_is_solid;
}

Renderer *Tile::renderer() const
{
    return m_renderer;
}
