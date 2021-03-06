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
    void bindKey(Qt::Key key, Control control);
    void defaultBinings();

    void makeMove(Board* board, EntitiesBag* bag, Tank* tank);
private:
    map<Qt::Key, Control> m_bind;
    int m_lives;
};

#endif // PLAYER_H
