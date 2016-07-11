#ifndef GAME_H
#define GAME_H

#include <QQuickPaintedItem>

class Game : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Game(QQuickItem* parent=nullptr);

    void paint(QPainter *painter);

    static void registerInQML();
};

#endif // GAME_H
