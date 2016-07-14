#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>
#include <utility>

#include "entities/tile.h"
#include "factories/tilebuilder.h"

class TileBuilder;
class Board : public QObject
{
    Q_OBJECT
public:
    Board(qreal width, qreal height, TileBuilder* builder);
    virtual ~Board();

    void loadBoard(QJsonObject &root);
    void resize(QSizeF newSize);
    QSizeF getTileRatio() const ;


    qreal getLeftCoord(Body* body);
    qreal getRightCoord(Body* body);
    qreal getUpperCoord(Body* body);
    qreal getLowerCoord(Body* body);
    bool collidesWithBoard(Body* body);
    bool inBoardBounds(Body* body);

    QList<Tile*> detectCollision(Body* body);
    QList<const Tile *> spawnableTiles();
signals:
    void baseDestroyed();

private slots:
    void destroyTile(Entity*);

protected:
    std::pair<std::pair<int,int>, std::pair<int,int> > mapBodyToTiles(Body* body);
    void connectTile(int index);
    qreal rightBound();
    qreal bottomBound();
    qreal leftBound();
    qreal topBound();
private:
    QList<int> m_base_tiles;
    Tile ** m_tiles;
    // REAL board size
    qreal m_board_width;
    qreal m_board_height;
    int m_rows, m_cols;
    TileBuilder* m_builder;
};

#endif // BOARD_H
