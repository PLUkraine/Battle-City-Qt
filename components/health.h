#ifndef HEALTH_H
#define HEALTH_H

#include "component.h"

class Health : public Component
{
    Q_OBJECT
public:
    Health(int points);

    void hit(int points);
    int health() const;

signals:
    void died(Entity*);
private:
    int m_health;
};

#endif // HEALTH_H
