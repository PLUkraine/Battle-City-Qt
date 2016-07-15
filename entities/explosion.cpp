#include "explosion.h"

Explosion::Explosion(Renderer *renderer, Body *body, int timeToLive)
    : Entity(),
      m_time_to_live(timeToLive)
{
    m_renderer = renderer;
    m_body = body;

    wire_renderer_to_body();
}

Explosion::~Explosion()
{
    unwire_renderer_from_body();
    dispose_of_renderer();
}

bool Explosion::mustDie() const
{
    return m_ticks_lived >= m_time_to_live-1;
}
