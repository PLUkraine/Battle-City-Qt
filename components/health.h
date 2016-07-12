#ifndef HEALTH_H
#define HEALTH_H

#include <QObject>

class Entity;
class Health : public QObject
{
    Q_OBJECT
public:
    Health(int points);

    void hit(int points);
    int health() const;

    Entity *owner() const;
    void setOwner(Entity *owner);

signals:
    void died(Entity*);
private:
    Entity* m_owner;
    int m_health;
};

#endif // HEALTH_H
