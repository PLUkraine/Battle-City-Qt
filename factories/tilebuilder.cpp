#include <QImage>
#include <QDebug>

#include "tilebuilder.h"

static const bool IS_SOLID[] = {
    false, true
};

TileBuilder::TileBuilder(Game *game, QImage* images)
    : m_game(game),
      m_width(0),
      m_height(0),
      m_images(images)
{
}

Tile *TileBuilder::createTile(TileBuilder::TileType type, QPointF pos)
{
    return createTile(type, pos.x(), pos.y());
}

Tile *TileBuilder::createTile(TileBuilder::TileType type, qreal x, qreal y)
{

    Body* body = new Body(x, y, m_width, m_height);
    Renderer* rend = new Renderer(&m_images[type], m_game);

    Tile * tile = new Tile(body, rend, IS_SOLID[type]);
    return tile;
}

void TileBuilder::setWidth(const qreal &width)
{
    m_width = width;
}

void TileBuilder::setHeight(const qreal &height)
{
    m_height = height;
}

qreal TileBuilder::width() const
{
    return m_width;
}

qreal TileBuilder::height() const
{
    return m_height;
}
