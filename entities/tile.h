#ifndef TILE_H
#define TILE_H

#include <QObject>

#include "components/body.h"
#include "components/renderer.h"

class Tile : public QObject
{
    Q_OBJECT
public:
    Tile(Body* body, Renderer* renderer, bool is_solid, QObject* parent=0);
    virtual ~Tile();

    Body *body() const;
    bool is_solid() const;

    Renderer *renderer() const;

private:
    Body* m_body;
    Renderer* m_renderer;

    bool m_is_solid;
};

#endif // TILE_H
