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
    void victory();
    void enemyLeftChanged(int val);
    void playerHealthChanged(int healthLeft);
public slots:
    void createAndStartGame(QString level);
    void pauseOrResumeGame();
    void stopGame();

    void playerHealthChange(int healthLeft);
    void enemyCountChanged();

    void updateGame();
    void activateGameOver();
    void activateVictory();
private:
    void cleanup();
    bool loadLevel(QString filename);

    QTimer timer;

    Board* board;
    Player* player;

    EntitiesBag* bag;

    bool m_game_created;
};

#endif // GAME_H
