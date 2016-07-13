#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class Entity;
class Component : public QObject
{
    Q_OBJECT
public:
    Component(Entity* owner=nullptr);

    Entity *owner() const;
    void setOwner(Entity *owner);

protected:
    Entity* m_owner;
};

#endif // COMPONENT_H
