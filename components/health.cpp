#include "health.h"

Health::Health(int points)
    : Component(),
      m_health(points)
{
}

void Health::hit(int points)
{
    if (m_health > 0) {
        m_health -= points;
        if (m_health <= 0 && m_owner)
            emit died(m_owner);
    }
}

int Health::health() const
{
    return m_health;
}
