#ifndef WEAPON_H
#define WEAPON_H

#include "components/component.h"

class Game;
class Bullet;
class Weapon : public Component
{
    Q_OBJECT
public:
    Weapon(Game *game, int ammo, int cooldown);
    virtual Bullet* shoot();
    int ammo() const;
    bool canShoot() const;
    void update();

signals:
    void shot();

protected:
    int m_ammo;
    int m_cooldown;
    int m_frames_passed;
    Game* m_game;
};

class StandartWeapon : public Weapon
{
    Q_OBJECT
public:
    StandartWeapon(Game* game);
    Bullet* shoot();

};

#endif // WEAPON_H
