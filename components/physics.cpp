#include "physics.h"

Physics::Physics(qreal max_speed)
    : QObject(nullptr),
      m_max_speed(max_speed)
{
}

void Physics::update(Body *body)
{
    qreal x = body->x();
    qreal y = body->y();
    switch (body->direction()) {
        case Direction::UP: y -= m_max_speed;  break;
        case Direction::DOWN: y += m_max_speed; break;
        case Direction::LEFT: x -= m_max_speed; break;
        case Direction::RIGHT: x+=m_max_speed; break;
    }
    body->setPosition(x, y);
}

void Physics::undo(Body *body)
{
    qreal x = body->x();
    qreal y = body->y();
    switch (body->direction()) {
        case Direction::UP: y += m_max_speed;  break;
        case Direction::DOWN: y -= m_max_speed; break;
        case Direction::LEFT: x += m_max_speed; break;
        case Direction::RIGHT: x-=m_max_speed; break;
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

