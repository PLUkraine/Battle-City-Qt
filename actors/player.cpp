#include <string.h>

#include "player.h"

#include "game/board.h"


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

void Player::makeMove(Board *board, Tank* tank)
{
    for (int i=0; i<=3; ++i)
    {
        if (m_control[i]) {
            tank->body()->setDirection(ControlToDirection((Control)i));
            tank->update();

            // update properly
            qreal x=tank->body()->x();
            qreal y=tank->body()->y();
            if (i == LEFT) {
                x = board->getRighTCoord(tank->body());
            } else if (i == RIGHT) {
                x = board->getLeftCoord(tank->body());
            } else if (i == UP) {
                y = board->getLowerCoord(tank->body());
            } else if (i == DOWN){
                y = board->getUpperCoord(tank->body());
            }

            tank->body()->setPosition(x, y);

            break;
        }
    }

}
