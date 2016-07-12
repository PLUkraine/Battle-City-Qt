#include <string.h>

#include "player.h"


Player::Player(QObject *parent) : Actor(parent)
{
    memset(m_control, 0, sizeof(m_control));

    m_bind[Qt::Key_Up] = UP;
    m_bind[Qt::Key_Right] = RIGHT;
    m_bind[Qt::Key_Down] = DOWN;
    m_bind[Qt::Key_Left] = LEFT;
}

void Player::setKey(Qt::Key key, bool value)
{
    if (m_bind.find(key) == m_bind.end()) return;

    m_control[m_bind[key]] = value;
}

void Player::makeMove(Board *, Tank* tank)
{
    for (int i=0; i<=3; ++i)
    {
        qreal speed = tank->physics()->max_speed();
        if (m_control[i]) {
            if (i == UP || i == DOWN) {
                tank->physics()->setYSpeed(i==UP ? -speed : speed);
                tank->physics()->setXSpeed(0);
            } else {
                tank->physics()->setXSpeed(i==LEFT ? -speed : speed);
                tank->physics()->setYSpeed(0);
            }

            tank->update();
            break;
        }
    }

}
