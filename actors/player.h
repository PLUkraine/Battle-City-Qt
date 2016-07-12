#ifndef PLAYER_H
#define PLAYER_H

#include <map>

#include "actors/actor.h"

using std::map;

class Player : public Actor
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    void setKey(Qt::Key key, bool value);

    void makeMove(Board *board, Tank *tank);
private:
    map<Qt::Key, Control> m_bind;
    bool m_control[CONTROLS_NUM];
};

#endif // PLAYER_H
