#include "tile.h"

Tile::Tile(Body *body, Renderer *renderer, Health *health, bool is_solid) : Entity(),
    m_is_solid(is_solid)
{
    m_body = body;
    m_renderer = renderer;
    m_health = health;

    m_body->setParent(this);
    m_health->setParent(this);

    wire_health();
    wire_renderer_to_body();
}

Tile::~Tile()
{
    unwire_renderer_from_body();
    dispose_of_renderer();
}

bool Tile::is_solid() const
{
    return m_is_solid;
}
