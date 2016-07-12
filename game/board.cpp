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
