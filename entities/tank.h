#ifndef TANK_H
#define TANK_H

#include "entities/entity.h"

class Tank : public Entity
{
public:
    Tank(Body* body, Renderer* renderer, Physics* physics, Health* health, Weapon *weapon);
    ~Tank();

    void update();
};

#endif // TANK_H
