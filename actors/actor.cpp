#include "actor.h"

Actor::Actor(QObject *parent) : QObject(parent)
{

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
