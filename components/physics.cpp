#include "physics.h"

Physics::Physics(qreal max_speed, Direction direction)
    : QObject(nullptr),
      m_max_speed(max_speed),
      m_direction(direction)
{
}

void Physics::update(Body *body)
{
    qreal x = body->x();
    qreal y = body->y();
    switch (m_direction) {
        case Direction::UP: y -= m_max_speed;  break;
        case Direction::DOWN: y += m_max_speed; break;
        case Direction::LEFT: x -= m_max_speed; break;
        case Direction::RIGHT: x+=m_max_speed; break;
    }
    body->setPosition(x, y);
}

qreal Physics::max_speed() const
{
    return m_max_speed;
}

void Physics::setMax_speed(qreal max_speed)
{
    m_max_speed = max_speed;
}

Direction Physics::direction() const
{
    return m_direction;
}

void Physics::setDirection(const Direction &direction)
{
    m_direction = direction;
}
