#ifndef TILE_H
#define TILE_H

#include <QObject>

#include "entities/entity.h"

class Tile : public Entity
{
    Q_OBJECT
public:
    Tile(Body* body, Renderer* renderer, Health* health, bool is_solid);
    virtual ~Tile();

    void update() {}
    bool is_solid() const;
private:
    bool m_is_solid;
};

#endif // TILE_H
