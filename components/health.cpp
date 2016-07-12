#include "health.h"


Entity *Health::owner() const
{
    return m_owner;
}

void Health::setOwner(Entity *owner)
{
    m_owner = owner;
}

Health::Health(int points)
    : QObject(nullptr),
      m_owner(nullptr),
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
