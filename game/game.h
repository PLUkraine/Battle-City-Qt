#ifndef GAME_H
#define GAME_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>

#include <set>

#include"game/board.h"
#include"actors/player.h"

class Board;
class Game : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Game(QQuickItem* parent=nullptr);
    virtual ~Game();

    void paint(QPainter *painter);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    static void registerInQML();

public slots:
    void updateGame();
private:
    QTimer timer;

    Board* board;
    Player* player;

    EntitiesBag* bag;
};

#endif // GAME_H
