#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>
#include <QDebug>

#include "board.h"



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
