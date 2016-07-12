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
    Body(qreal x, qreal y, int width, int height);

    qreal x() const;
    qreal y() const;
    void setPosition(qreal x, qreal y);
    QPointF pos() const;

    qreal width() const;
    qreal height() const;
    void setSize(qreal width, qreal height);

    bool collidesWith(Body* other);

    QRectF boundingRect() const;

signals:
    void positionChanged(qreal, qreal);
    void sizeChanged(qreal, qreal);

private:
    qreal m_x, m_y;
    qreal m_width, m_height;
};

#endif
