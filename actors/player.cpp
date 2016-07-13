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
    move(tank, board, bag);
    shoot(tank->weapon(), bag);
}
