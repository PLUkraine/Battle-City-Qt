#ifndef BODY_H
#define BODY_H

#include <QObject>

/**
 * @brief The Body class - the physical body of some entity
 */
class Body : public QObject
{
    Q_OBJECT
public:
    Body(qreal x, qreal y, int width, int height, qreal speed);

    qreal x() const;
    qreal y() const;
    void setPosition(qreal x, qreal y);
    QPointF pos() const;

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    qreal speed() const;
    void setSpeed(const qreal &speed);

    bool collidesWith(Body* other);

    QRectF boundingRect() const;

signals:
    void positionChanged(qreal, qreal);

private:
    qreal m_x, m_y;
    int m_width, m_height;
    qreal m_speed;
};

#endif
