#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>

#include "entities/tank.h"

class Board;
class EntitiesBag;
class Actor : public QObject
{
    Q_OBJECT
public:
    enum Control { UP, DOWN, LEFT, RIGHT, SHOOT };
    static const int CONTROLS_NUM = 4;

    Actor(QObject *parent = 0);
    virtual void makeMove(Board* board, EntitiesBag* bag, Tank* tank)=0;

    static void correctToTiles(Board* board, Body* body);
    static void correctToTanks(EntitiesBag* bag, Entity *entity);
    Direction ControlToDirection(Control c);
};

#endif // ACTOR_H
