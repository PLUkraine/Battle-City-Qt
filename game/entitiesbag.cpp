#include "entitiesbag.h"

EntitiesBag::EntitiesBag(Tank *playerTank)
    : m_playerTank(playerTank)

{
}

EntitiesBag::~EntitiesBag()
{
    for (Tank* tank: m_tanks)
        delete tank;
    for (Bullet* bullet : m_bullets)
        delete bullet;
    delete m_playerTank;
}

bool EntitiesBag::collidesWith(Body *body)
{
    for (Tank* t : m_tanks)
        if (t->body()->collidesWith(body) && t->body() != body)
            return true;

    return m_playerTank->body()->collidesWith(body)
            && m_playerTank->body() != body;
}

void EntitiesBag::update(Actor *player, Board *board)
{
    player->makeMove(board, this, m_playerTank);
}

void EntitiesBag::addTank(Tank *t)
{
    m_tanks.insert(t);
}
