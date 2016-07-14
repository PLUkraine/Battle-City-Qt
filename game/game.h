#ifndef GAME_H
#define GAME_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>

#include <set>

#include"actors/player.h"

class Board;
class Game : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Game(QQuickItem* parent=nullptr);
    virtual ~Game();

    void paint(QPainter *painter);
    QSizeF getRatioFromBoard() const;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    static void registerInQML();

signals:
    void gameOver();
public slots:
    void createAndStartGame(QString level);
    void pauseOrResumeGame();
    void stopGame();

    void updateGame();
    void activateGameOver();
private:
    void cleanup();
    bool loadLevel(QString filename);

    QTimer timer;

    Board* board;
    Player* player;

    EntitiesBag* bag;
};

#endif // GAME_H
