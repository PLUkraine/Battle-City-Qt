#ifndef PHYSICS_H
#define PHYSICS_H
#include "components/body.h"

#include <QList>

class Physics : public QObject
{
    Q_OBJECT
public:
    Physics(qreal max_speed);

    void update(Body* body);

    qreal max_speed() const;
    void setMax_speed(qreal max_speed);



    qreal x_speed() const;
    void setXSpeed(qreal x_speed);

    qreal y_speed() const;
    void setYSpeed(qreal y_speed);

private:
    qreal m_x_speed;
    qreal m_y_speed;
    qreal m_max_speed;
};

#endif // PHYSICS_H
