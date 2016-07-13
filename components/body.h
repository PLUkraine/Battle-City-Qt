#ifndef BODY_H
#define BODY_H

#include "component.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

/**
 * @brief The Body class - the physical body of some entity
 */
class Body : public Component
{
    Q_OBJECT
public:
    Body(qreal x, qreal y, qreal width, qreal height, Direction direction);

    qreal x() const;
    qreal y() const;
    void setPosition(qreal x, qreal y);
    QPointF pos() const;

    qreal width() const;
    qreal height() const;
    void setSize(qreal width, qreal height);

    bool collidesWith(Body* other);

    QRectF boundingRect() const;

    Direction direction() const;
    void setDirection(const Direction &direction);

signals:
    void positionChanged(qreal, qreal);
    void sizeChanged(qreal, qreal);
    void directionChanged(Direction);

private:
    qreal m_x, m_y;
    qreal m_width, m_height;
    Direction m_direction;
};

#endif
