#ifndef GAME_H
#define GAME_H

#include <QQuickPaintedItem>
#include <QImage>

#include"entities/tile.h"

class Game : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Game(QQuickItem* parent=nullptr);

    void paint(QPainter *painter);

    static void registerInQML();
private:
    QImage tileSprites[2];
};

#endif // GAME_H
