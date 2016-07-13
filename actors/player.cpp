#include <string.h>

#include "player.h"

#include "game/board.h"
#include"game/entitiesbag.h"


Player::Player(QObject *parent) : Actor(parent)
{
    memset(m_control, 0, sizeof(m_control));

    m_bind[Qt::Key_Up] = UP;
    m_bind[Qt::Key_Right] = RIGHT;
    m_bind[Qt::Key_Down] = DOWN;
    m_bind[Qt::Key_Left] = LEFT;
    m_bind[Qt::Key_Space] = SHOOT;
}

void Player::setKey(Qt::Key key, bool value)
{
    if (m_bind.find(key) == m_bind.end()) return;

    m_control[m_bind[key]] = value;
}

void Player::makeMove(Board *board, EntitiesBag *bag, Tank* tank)
{
    int i=0;
    for (i=0; i<=3; ++i)
    {
        if (m_control[i]) {
            tank->body()->setDirection(ControlToDirection((Control)i));
            tank->physics()->setSpeed(tank->physics()->max_speed());
            tank->update();

            correctToTanks(bag, tank);
            correctToTiles(board, tank->body());

            break;
        }
    }
    if (i == 4) {
        tank->physics()->setSpeed(0);
        tank->update();
    }

    if (m_control[SHOOT] && tank->weapon()->canShoot()) {
        bag->addBullet(tank->weapon()->shoot());
    }

}
