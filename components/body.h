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
    Body(int x, int y, int width, int height);

    int x() const;
    int y() const;
    void setPosition(int x, int y);
    QPoint pos() const;

    int width() const;
    int height() const;
    void setSize(int width, int height);

    bool collidesWith(Body* other);

    QRect boundingRect() const;

signals:
    void positionChanged(int, int);
    void sizeChanged(int, int);

private:
    int m_x, m_y;
    int m_width, m_height;
};

#endif
