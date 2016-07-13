#include "component.h"

Component::Component(Entity *owner)
    :QObject(nullptr),
      m_owner(owner)
{

}

Entity *Component::owner() const
{
    return m_owner;
}

void Component::setOwner(Entity *owner)
{
    m_owner = owner;
}
