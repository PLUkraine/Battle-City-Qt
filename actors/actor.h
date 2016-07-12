#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>

#include "entities/tank.h"

class Board;
class Actor : public QObject
{
    Q_OBJECT
public:
    enum Control { UP, DOWN, LEFT, RIGHT };
    static const int CONTROLS_NUM = 4;

    Actor(QObject *parent = 0);
    virtual void makeMove(Board* board, Tank* tank)=0;
    Direction ControlToDirection(Control c);
};

#endif // ACTOR_H
