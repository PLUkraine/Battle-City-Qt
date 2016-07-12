#ifndef PHYSICS_H
#define PHYSICS_H
#include "components/body.h"

#include <QList>

class Physics : public QObject
{
    Q_OBJECT
public:
    Physics(int max_speed);

    void update(Body* body);

    int max_speed() const;
    void setMax_speed(int max_speed);



    int x_speed() const;
    void setXSpeed(int x_speed);

    int y_speed() const;
    void setYSpeed(int y_speed);

private:
    int m_x_speed;
    int m_y_speed;
    int m_max_speed;
};

#endif // PHYSICS_H
