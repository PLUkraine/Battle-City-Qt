#ifndef GAME_H
#define GAME_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>

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
    QImage tileSprites[2];
    QImage tankSprite;

    QTimer timer;

    Board* board;
    Player* player;
    Tank* playerTank;


};

#endif // GAME_H
