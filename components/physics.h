#ifndef PHYSICS_H
#define PHYSICS_H
#include "components/body.h"


class Physics : public Component
{
    Q_OBJECT
public:
    Physics(qreal max_speed);

    void update(Body* body);
    void undo(Body* body);

    qreal max_speed() const;


    qreal speed() const;
    void setSpeed(const qreal &speed);

private:
    qreal m_max_speed;
    qreal m_speed;
};

#endif // PHYSICS_H
