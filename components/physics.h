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
    void undo(Body* body);

    qreal max_speed() const;
    void setMax_speed(qreal max_speed);

private:
    qreal m_max_speed;
};

#endif // PHYSICS_H
