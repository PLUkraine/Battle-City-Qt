#include "actor.h"
#include"game/board.h"

Actor::Actor(QObject *parent) : QObject(parent)
{

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
