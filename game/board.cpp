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

    builder->setHeight(m_board_height / rows);
    builder->setWidth(m_board_width / cols);

    m_tiles = new Tile*[cols*rows];
    for (int i=0; i<cols*rows; ++i) {
        qreal y = (i / cols) * builder->height();
        qreal x = (i % cols) * builder->width();
        m_tiles[i] = builder->createTile((TileBuilder::TileType)data[i].toInt(), x, y);
        m_tiles[i]->setParent(this);
    }

    // TODO check if object is out of bounds, or do it separately


}

void Board::resize(QSizeF newSize)
{
    m_board_height = newSize.height();
    m_board_width = newSize.width();

    QSizeF tileSize(m_board_width / m_cols, m_board_height / m_rows);

    for (int i=0; i<m_cols*m_rows; ++i) {
        qreal y = (i / m_cols) * tileSize.height();
        qreal x = (i % m_cols) * tileSize.width();
        m_tiles[i]->body()->setPosition(x, y);
        m_tiles[i]->body()->setSize(tileSize.width(), tileSize.height());
    }
}

bool Board::intersectsTiles(Body *body)
{
    qreal t_width = m_board_width / m_cols;
    qreal t_height = m_board_height / m_rows;

    int left_tile = body->boundingRect().left() / t_width;
    int right_tile = body->boundingRect().right() / t_width;
    int upper_tile = body->boundingRect().top() / t_height;
    int lower_tile = body->boundingRect().bottom() / t_height;

//    qDebug() << left_tile << right_tile;
//    qDebug() << upper_tile << lower_tile;

    bool intersects = false;
    for (int i = max(left_tile, 0); i<= min(right_tile, m_rows - 1); ++i) {
        for (int j = max(upper_tile, 0); j<= min(lower_tile, m_cols - 1); ++j) {
            int index = i*m_cols + j;
            //qDebug() << i << j << index << m_tiles[index]->body()->boundingRect() << body->boundingRect();
            intersects |= m_tiles[index]->body()->collidesWith(body)
                    && m_tiles[index]->is_solid();
        }
    }

    return intersects;
}
