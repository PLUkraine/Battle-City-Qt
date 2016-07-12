#include "physics.h"

Physics::Physics(int max_speed)
    : QObject(nullptr),
      m_x_speed(0),
      m_y_speed(0),
      m_max_speed(max_speed)
{
}

void Physics::update(Body *body)
{
    body->setPosition(body->x() + m_x_speed, body->y() + m_y_speed);
}

int Physics::max_speed() const
{
    return m_max_speed;
}

void Physics::setMax_speed(int max_speed)
{
    m_max_speed = max_speed;
}

int Physics::x_speed() const
{
    return m_x_speed;
}

void Physics::setXSpeed(int x_speed)
{
    m_x_speed = x_speed;
}

int Physics::y_speed() const
{
    return m_y_speed;
}

void Physics::setYSpeed(int y_speed)
{
    m_y_speed = y_speed;
}
