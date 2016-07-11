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



int Body::width() const
{
    return m_width;
}

int Body::height() const
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


qreal Body::speed() const
{
    return m_speed;
}

void Body::setSpeed(const qreal &speed)
{
    m_speed = speed;
}

bool Body::collidesWith(Body *other)
{
    return boundingRect().intersects(other->boundingRect());
}

QRectF Body::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

Body::Body(qreal x, qreal y, qreal width, qreal height, qreal speed)
    : QObject(nullptr),
      m_x(x), m_y(y),
      m_width(width),
      m_height(height),
      m_speed(speed)
{
}
