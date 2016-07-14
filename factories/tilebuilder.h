#ifndef TILEBUILDER_H
#define TILEBUILDER_H
#include "entities/tile.h"
#include "entitiesfactory.h"
#include "utils/resoursecontainer.h"

class EntitiesFactory;
class TileBuilder : public EntitiesFactory
{
public:
    enum TileType { AIR, WALL, BASE, STEEL };

    TileBuilder(Game* game);

    Tile* createTile(TileType type, QPointF pos);
    Tile* createTile(TileType type, qreal x, qreal y);

protected:
};

#endif // TILEBUILDER_H
