#ifndef PHYSICS_H
#define PHYSICS_H
#include "components/body.h"

#include <QList>

class Physics : public QObject
{
    Q_OBJECT
public:
    Physics();

private:
    qreal m_speed;

};

#endif // PHYSICS_H
