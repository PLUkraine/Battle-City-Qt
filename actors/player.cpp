#include <string.h>

#include "player.h"

#include "game/board.h"
#include"game/entitiesbag.h"


Player::Player(QObject *parent) : Actor(parent)
{
    memset(m_control, 0, sizeof(m_control));

    defaultBinings();
}

void Player::setKey(Qt::Key key, bool value)
{
    if (m_bind.find(key) == m_bind.end()) return;

    m_control[m_bind[key]] = value;
}

void Player::bindKey(Qt::Key key, Actor::Control control)
{
    for (auto it = m_bind.begin(); it != m_bind.end(); ++it) {
        if (it->second == control) {
            m_bind.erase(it);
            break;
        }
    }
    m_bind.insert(std::make_pair(key, control));
}

void Player::defaultBinings()
{
    m_bind[Qt::Key_Up] = UP;
    m_bind[Qt::Key_Right] = RIGHT;
    m_bind[Qt::Key_Down] = DOWN;
    m_bind[Qt::Key_Left] = LEFT;
    m_bind[Qt::Key_Space] = SHOOT;
}

void Player::makeMove(Board *board, EntitiesBag *bag, Tank* tank)
{
    move(tank, board, bag);
    shoot(tank->weapon(), bag);
}
