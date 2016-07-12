#ifndef PHYSICS_H
#define PHYSICS_H
#include "components/body.h"

#include <QList>

class Physics : public QObject
{
    Q_OBJECT
public:
    Physics(qreal max_speed, Direction direction);

    void update(Body* body);

    qreal max_speed() const;
    void setMax_speed(qreal max_speed);

    Direction direction() const;
    void setDirection(const Direction &direction);

private:
    Direction m_direction;
    qreal m_max_speed;
};

#endif // PHYSICS_H
