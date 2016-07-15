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
    enum GameError { NO_ERROR, LEVEL_NOT_FOUND, LEVEL_FILE_CORRUPTED };
    Q_ENUM(GameError)

    Game(QQuickItem* parent=nullptr);
    virtual ~Game();

    void paint(QPainter *painter);
    QSizeF getRatioFromBoard() const;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    static void registerInQML();

    Q_INVOKABLE GameError getLastError() const;

signals:
    void gameOver();
    void victory();
    void enemyLeftChanged(int val);
    void playerHealthChanged(int healthLeft);
    void gameStarted(int, int);
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
    GameError m_lastError;
};

#endif // GAME_H
