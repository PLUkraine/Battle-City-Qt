#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include "components/body.h"
#include "components/renderer.h"
#include "components/physics.h"
#include "components/health.h"
#include "components/weapon.h"

class Entity : public QObject
{
    Q_OBJECT
public:
    Entity();
    virtual ~Entity() {}

    Renderer *renderer() const;

    Body *body() const;

    Physics *physics() const;

    virtual void update(); // ? maybe not

    Health *health() const;

    Weapon *weapon() const;

protected:
    // connect body change signals to the renderer
    void wire_renderer_to_body();
    // disconnect body from the renderer
    void unwire_renderer_from_body();
    // connect health to this entity
    void wire_health();
    // connect weapon to this entity
    void wire_weapon();

    // destroy the renderer
    void dispose_of_renderer();

    Renderer* m_renderer;
    Body* m_body;
    Physics *m_physics;
    Health* m_health;
    Weapon* m_weapon;

    // int m_ticks_lived; // maybe later
};

#endif // ENTITY_H
