#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include "components/body.h"
#include "components/renderer.h"

class Entity : public QObject
{
    Q_OBJECT
public:
    Entity();
    virtual ~Entity() {}

    Renderer *renderer() const;

    Body *body() const;

    virtual void update()=0; // ? maybe not

protected:
    // connect body change to the renderer
    void wire_renderer_to_body();
    // disconnect body from the renderer
    void unwire_renderer_from_body();

    // destroy the renderer
    void dispose_of_renderer();

    Renderer* m_renderer;
    Body* m_body;
};

#endif // ENTITY_H
