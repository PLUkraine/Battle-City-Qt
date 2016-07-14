#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <algorithm>

#include "board.h"

using std::min;
using std::max;

typedef std::pair<int,int> pii;
typedef std::pair<pii, pii> range_p;


Board::Board(qreal width, qreal height, TileBuilder *builder)
    :QObject(nullptr),
      m_tiles(nullptr),
      m_board_width(width),
      m_board_height(height),
      m_rows(0),
      m_cols(0),
      m_builder(builder)
{
}

Board::~Board()
{
    if (m_tiles) {
        delete[] m_tiles;
    }
    delete m_builder;
}

void Board::loadBoard(QJsonObject& root)
{
    QJsonArray data = root["data"].toArray();

    int cols = root["cols"].toInt();
    int rows = root["rows"].toInt();
    m_cols = cols;
    m_rows = rows;

    // map tiles to the real coordinates
    m_builder->setRatio(m_board_width / (cols * m_builder->width()),
                      m_board_height / (rows * m_builder->height()));

    m_base_tiles.clear();
    m_tiles = new Tile*[cols*rows];
    for (int i=0; i<cols*rows; ++i) {
        int y = (i / cols) * m_builder->height();
        int x = (i % cols) * m_builder->width();
        int type = data[i].toInt();
        m_tiles[i] = m_builder->createTile((TileBuilder::TileType)type, x, y);
        if (type == TileBuilder::BASE) {
            m_base_tiles.append(i);
        }
        connectTile(i);
    }

}

void Board::resize(QSizeF newSize)
{
    m_board_height = newSize.height();
    m_board_width = newSize.width();

    QSizeF tileSize = getTileRatio();

    for (int i=0; i<m_cols*m_rows; ++i) {
        m_tiles[i]->renderer()->setRatio(tileSize);
    }
}

QSizeF Board::getTileRatio() const
{
    QSizeF tileSize(m_board_width / (m_cols * m_tiles[0]->body()->width()),
            m_board_height / (m_rows * m_tiles[0]->body()->height()) );
    return tileSize;
}

qreal Board::getLeftCoord(Body *body)
{
    range_p r = mapBodyToTiles(body);
    for (int i=max(0,r.second.first); i<=min(r.second.second, m_rows-1); i++) {
        for (int j=max(0,r.first.first); j<=min(r.first.second, m_cols-1); ++j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];

            //qDebug() << tile->body()->boundingRect() << i << j;

            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
                return tile->body()->boundingRect().left() - body->width();
            }
        }
    }
    if (body->x() > rightBound()-body->width()) {
        return rightBound()-body->width();
    } else if (body->x() < leftBound()) {
        return leftBound();
    }
    return body->x();
}

qreal Board::getRightCoord(Body *body)
{
    range_p r = mapBodyToTiles(body);
    for (int i=min(r.second.second, m_rows-1); i>=max(0,r.second.first); i--) {
        for (int j=max(0,r.first.first); j<=min(r.first.second, m_cols-1); ++j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];

            //qDebug() << tile->body()->boundingRect() << i << j;

            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
                return tile->body()->boundingRect().right();
            }
        }
    }
    if (body->x() > rightBound()-body->width()) {
        return rightBound()-body->width();
    } else if (body->x() < leftBound()) {
        return leftBound();
    }
    return body->x();
}

qreal Board::getUpperCoord(Body *body)
{
    range_p r = mapBodyToTiles(body);
    for (int i=min(r.second.second, m_rows-1); i>=max(0,r.second.first); i--) {
        for (int j=max(0,r.first.first); j<=min(r.first.second, m_cols-1); ++j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];

            //qDebug() << tile->body()->boundingRect() << i << j;

            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
                return tile->body()->boundingRect().top() - body->height();
            }
        }
    }
    if (body->y() > bottomBound()-body->height()) {
        return bottomBound()-body->height();
    } else if (body->y() < topBound()) {
        return topBound();
    }
    return body->y();
}

qreal Board::getLowerCoord(Body *body)
{
    range_p r = mapBodyToTiles(body);
    for (int i=min(r.second.second, m_rows-1); i>=max(0,r.second.first); i--) {
        for (int j=min(r.first.second, m_cols-1); j>=max(0,r.first.first); --j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];

            //qDebug() << tile->body()->boundingRect() << i << j;

            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
                return tile->body()->boundingRect().bottom();
            }
        }
    }
    if (body->y() > bottomBound()-body->height()) {
        return bottomBound()-body->height();
    } else if (body->y() < topBound()) {
        return topBound();
    }
    return body->y();
}

bool Board::collidesWithBoard(Body *body)
{
    range_p r = mapBodyToTiles(body);
    for (int i=max(0,r.second.first); i<=min(r.second.second, m_rows-1); i++) {
        for (int j=max(0,r.first.first); j<=min(r.first.second, m_cols-1); ++j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];
            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
                return true;
            }
        }
    }
    return false;
}

bool Board::inBoardBounds(Body *body)
{
    QRectF r(topBound(), leftBound(), rightBound(), bottomBound());
    return r.contains(body->boundingRect().topLeft()) && r.contains(body->boundingRect().bottomRight());
}

QList<Tile *> Board::detectCollision(Body *body)
{
    QList<Tile*> tiles;

    range_p r = mapBodyToTiles(body);
    for (int i=max(0,r.second.first); i<=min(r.second.second, m_rows-1); i++) {
        for (int j=max(0,r.first.first); j<=min(r.first.second, m_cols-1); ++j) {
            int index = i*m_cols + j;
            Tile* tile = m_tiles[index];
            bool coll = body->collidesWith(tile->body());
            coll &= tile->is_solid();
            if ( coll ) {
               tiles.append(tile);
            }
        }
    }
    return tiles;
}

QList<const Tile *> Board::spawnableTiles()
{
    QList<const Tile *> result;
    for (int i=0; i<m_cols*m_rows; ++i) {
        if (!m_tiles[i]->is_solid()) {
            result.append(m_tiles[i]);
        }
    }
    return result;
}

void Board::destroyTile(Entity *e)
{
    range_p r = mapBodyToTiles(e->body());
    int index = r.second.first*m_cols + r.first.first;
    if (m_base_tiles.contains(index)) {
        m_base_tiles.removeOne(index);
        emit baseDestroyed();
    }

    m_tiles[index] = m_builder->createTile(TileBuilder::AIR, e->body()->pos());
    connectTile(index);

    disconnect(e->health(), SIGNAL(died(Entity*)), this, SLOT(destroyTile(Entity*)));
    e->setParent(nullptr);
    delete e;
}

void Board::connectTile(int index)
{
    m_tiles[index]->setParent(this);
    connect(m_tiles[index]->health(), SIGNAL(died(Entity*)), this, SLOT(destroyTile(Entity*)));
}

range_p Board::mapBodyToTiles(Body *body)
{
    qreal tile_w = m_tiles[0]->body()->width();
    qreal tile_h = m_tiles[0]->body()->height();
    pii left_to_right(body->boundingRect().left()/tile_w, body->boundingRect().right()/tile_w);
    pii up_to_down(body->boundingRect().top()/tile_h, body->boundingRect().bottom()/tile_h);
    return range_p(left_to_right, up_to_down);
}

qreal Board::rightBound()
{
    return m_cols * m_tiles[0]->body()->width();
}

qreal Board::bottomBound()
{
    return m_rows * m_tiles[0]->body()->height();
}

qreal Board::leftBound()
{
    return 0;
}

qreal Board::topBound()
{
    return 0;
}
