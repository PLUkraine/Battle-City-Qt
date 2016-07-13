#include "physics.h"

Physics::Physics(qreal max_speed)
    : Component(),
      m_max_speed(max_speed),
      m_speed(0)
{
}

void Physics::update(Body *body)
{
    qreal x = body->x();
    qreal y = body->y();
    switch (body->direction()) {
        case Direction::UP: y -= m_speed;  break;
        case Direction::DOWN: y += m_speed; break;
        case Direction::LEFT: x -= m_speed; break;
        case Direction::RIGHT: x+=m_speed; break;
    }
    body->setPosition(x, y);
}

void Physics::undo(Body *body)
{
    qreal x = body->x();
    qreal y = body->y();
    switch (body->direction()) {
        case Direction::UP: y += m_speed;  break;
        case Direction::DOWN: y -= m_speed; break;
        case Direction::LEFT: x += m_speed; break;
        case Direction::RIGHT: x-=m_speed; break;
    }
    body->setPosition(x, y);
}

qreal Physics::max_speed() const
{
    return m_max_speed;
}

qreal Physics::speed() const
{
    return m_speed;
}

void Physics::setSpeed(const qreal &speed)
{
    m_speed = speed;
}

