#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>
#include <QDebug>
#include <algorithm>

#include "board.h"

using std::min;
using std::max;


Board::Board(qreal width, qreal height)
    :QObject(nullptr),
      m_tiles(nullptr),
      m_board_width(width),
      m_board_height(height),
      m_rows(0),
      m_cols(0)
{
}

Board::~Board()
{
    if (m_tiles) {
        delete[] m_tiles;
    }
}

void Board::loadBoard(QString filename, TileBuilder *builder)
{
    QFile inFile(filename);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = inFile.readAll();
    inFile.close();

    QJsonParseError er;
    QJsonDocument doc = QJsonDocument::fromJson(val, &er);
    QJsonObject root = doc.object();
    QJsonArray data = root["data"].toArray();

    int cols = root["cols"].toInt();
    int rows = root["rows"].toInt();
    m_cols = cols;
    m_rows = rows;

    // map tiles to the real coordinates
    builder->setRatio(m_board_width / (cols * builder->width()),
                      m_board_height / (rows * builder->height()));

    m_tiles = new Tile*[cols*rows];
    for (int i=0; i<cols*rows; ++i) {
        int y = (i / cols) * builder->height();
        int x = (i % cols) * builder->width();
        m_tiles[i] = builder->createTile((TileBuilder::TileType)data[i].toInt(), x, y);
        m_tiles[i]->setParent(this);
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

bool Board::intersectsTiles(Body *)
{
    return true;
}

QSizeF Board::getTileRatio()
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
                return tile->body()->boundingRect().left()-tile->body()->width();
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

qreal Board::getRighTCoord(Body *body)
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
                return tile->body()->boundingRect().top() - tile->body()->height();
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
