#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>

#include "entities/tile.h"
#include "factories/tilebuilder.h"

class Board : public QObject
{
    Q_OBJECT
public:
    Board(qreal width, qreal height);
    virtual ~Board();

    void loadBoard(QString filename, TileBuilder* builder);
    void resize(QSizeF newSize);
    bool intersectsTiles(Body* body);
private:
    Tile ** m_tiles;
    // REAL board size
    qreal m_board_width;
    qreal m_board_height;
    int m_rows, m_cols;
};

#endif // BOARD_H
