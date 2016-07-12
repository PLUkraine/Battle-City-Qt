#ifndef TILEBUILDER_H
#define TILEBUILDER_H
#include "entities/tile.h"
#include "game/game.h"

class Game;
class TileBuilder
{
public:
    enum TileType { AIR, WALL };

    TileBuilder(Game* game, QImage *images);

    Tile* createTile(TileType type, QPointF pos);
    Tile* createTile(TileType type, qreal x, qreal y);

    void setSize(qreal tileSize);
    void setRatio(qreal x_ratio, qreal y_ratio);

    qreal width() const;
    qreal height() const;

protected:
    Game* m_game;
    qreal m_width, m_height;
    qreal m_x_ratio, m_y_ratio;
    QImage* m_images;
};

#endif // TILEBUILDER_H
