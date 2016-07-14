#include <QImage>
#include <QDebug>

#include "tilebuilder.h"
#include "factories/entitiesfactory.h"

TileBuilder::TileBuilder(Game *game)
    : EntitiesFactory(game)
{
    setSize(ResBag::get().tileSize());
}

Tile *TileBuilder::createTile(TileBuilder::TileType type, QPointF pos)
{
    return createTile(type, pos.x(), pos.y());
}

Tile *TileBuilder::createTile(TileBuilder::TileType type, qreal x, qreal y)
{

    Body* body = new Body(x, y, m_width, m_height, Direction::UP);
    Renderer* rend = new StaticRenderer(&ResBag::get().tilesSptites()[type], m_x_ratio, m_y_ratio, m_game);
    rend->setZ(-1);
    Health* health = new Health(ResBag::get().tileHealth()[type]);

    Tile * tile = new Tile(body, rend, health, ResBag::get().tileSolidness()[type]);
    return tile;
}
