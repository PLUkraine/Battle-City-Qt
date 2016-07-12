#include "body.h"
#include<QRectF>

qreal Body::x() const
{
    return m_x;
}


qreal Body::y() const
{
    return m_y;
}

void Body::setPosition(qreal x, qreal y)
{
    if (m_x != x || m_y != y) {
        m_x = x;
        m_y = y;
        emit positionChanged(x, y);
    }
}

QPointF Body::pos() const
{
    return QPointF(m_x, m_y);
}



qreal Body::width() const
{
    return m_width;
}

qreal Body::height() const
{
    return m_height;
}


void Body::setSize(qreal width, qreal height)
{
    if (width!=m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
        emit sizeChanged(width, height);
    }
}

bool Body::collidesWith(Body *other)
{
    return boundingRect().intersects(other->boundingRect());
}

QRectF Body::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

Direction Body::direction() const
{
    return m_direction;
}

void Body::setDirection(const Direction &direction)
{
    m_direction = direction;
}

Body::Body(qreal x, qreal y, qreal width, qreal height, Direction direction)
    : QObject(nullptr),
      m_x(x), m_y(y),
      m_width(width),
      m_height(height),
      m_direction(direction)
{
}
