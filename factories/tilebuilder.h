#ifndef TILEBUILDER_H
#define TILEBUILDER_H
#include "entities/tile.h"
#include "game/game.h"

class TileBuilder
{
public:
    enum TileType { AIR, WALL };

    TileBuilder(Game* game, QImage *images);

    Tile* createTile(TileType type, QPointF pos);
    Tile* createTile(TileType type, qreal x, qreal y);

    void setWidth(const qreal &width);
    void setHeight(const qreal &height);
    qreal width() const;
    qreal height() const;

protected:
    Game* m_game;
    qreal m_width, m_height;
    QImage* m_images;
};

#endif // TILEBUILDER_H
