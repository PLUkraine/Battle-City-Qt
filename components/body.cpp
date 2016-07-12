#include "body.h"
#include<QRectF>

int Body::x() const
{
    return m_x;
}


int Body::y() const
{
    return m_y;
}

void Body::setPosition(int x, int y)
{
    if (m_x != x || m_y != y) {
        m_x = x;
        m_y = y;
        emit positionChanged(x, y);
    }
}

QPoint Body::pos() const
{
    return QPoint(m_x, m_y);
}



int Body::width() const
{
    return m_width;
}

int Body::height() const
{
    return m_height;
}


void Body::setSize(int width, int height)
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

QRect Body::boundingRect() const
{
    return QRect(m_x, m_y, m_width, m_height);
}

Body::Body(int x, int y, int width, int height)
    : QObject(nullptr),
      m_x(x), m_y(y),
      m_width(width),
      m_height(height)
{
}
