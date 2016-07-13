#include "actor.h"
#include"game/board.h"
#include"game/entitiesbag.h"

Actor::Actor(QObject *parent) : QObject(parent)
{
    memset(m_control, 0, sizeof(m_control));
}

void Actor::correctToTiles(Board *board, Body *body)
{
    qreal x=body->x();
    qreal y=body->y();

    switch (body->direction()) {
        case Direction::LEFT: x = board->getRighTCoord(body); break;
        case Direction::RIGHT: x = board->getLeftCoord(body); break;
        case Direction::UP: y = board->getLowerCoord(body); break;
        case Direction::DOWN: y = board->getUpperCoord(body); break;
    }

    body->setPosition(x, y);
}

void Actor::correctToTanks(EntitiesBag *bag, Entity *entity)
{
    if (bag->collidesWithTank(entity->body()))
        entity->physics()->undo(entity->body());

}

Direction Actor::ControlToDirection(Actor::Control c)
{
    switch (c) {
    case UP:
        return Direction::UP;
        break;
    case DOWN:
        return Direction::DOWN;
        break;
    case LEFT:
        return Direction::LEFT;
        break;
    case RIGHT:
        return Direction::RIGHT;
        break;
    default:
        exit(1);
        break;
    }

}

void Actor::shoot(Weapon *w, EntitiesBag* bag)
{
    if (m_control[SHOOT] && w->canShoot()) {
        bag->addBullet(w->shoot());
    }
}

void Actor::move(Entity *tank, Board *board, EntitiesBag *bag)
{
    int i=0;
    for (i=0; i<=3; ++i)
    {
        if (m_control[i]) {
            tank->body()->setDirection(ControlToDirection((Control)i));
            tank->physics()->setSpeed(tank->physics()->max_speed());
            break;
        }
    }
    if (i == 4) {
        tank->physics()->setSpeed(0);
    }

    tank->update();
    correctToTanks(bag, tank);
    correctToTiles(board, tank->body());
}
