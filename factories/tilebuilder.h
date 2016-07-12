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

    Tile* createTile(TileType type, QPoint pos);
    Tile* createTile(TileType type, int x, int y);

    void setSize(int tileSize);
    void setRatio(qreal x_ratio, qreal y_ratio);

    int width() const;
    int height() const;

protected:
    Game* m_game;
    int m_width, m_height;
    qreal m_x_ratio, m_y_ratio;
    QImage* m_images;
};

#endif // TILEBUILDER_H
