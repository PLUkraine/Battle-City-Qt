#include <string.h>

#include "dummyai.h"
#include"game/entitiesbag.h"

DummyAI::DummyAI(QObject *parent)
    : Actor(parent),
      rd(),
      gen(rd()),
      dist(0.0, 0.99999),
      m_togo(0)
{

}

void DummyAI::makeMove(Board *board, EntitiesBag *bag, Tank *tank)
{
    if (m_togo > 0) {
        move(tank, board, bag);
        m_togo--;
    } else {
        // up to 9 frames
        m_togo = int(dist(gen) * 8) + 1;
        memset(m_control, 0, sizeof(m_control));
        int c = (int)(dist(gen) * 4);
        m_control[c] = true;
    }

    if (dist(gen) > 0.3) {
        m_control[SHOOT] = true;
        shoot(tank->weapon(), bag);
        m_control[SHOOT] = false;
    }
}
