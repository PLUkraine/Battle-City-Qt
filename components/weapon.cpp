#include "weapon.h"
#include "renderer.h"
#include "entities/bullet.h"
#include "utils/resoursecontainer.h"
#include "game/game.h"

Weapon::Weapon(Game *game, int ammo, int cooldown)
    : Component(),
      m_ammo(ammo),
      m_cooldown(cooldown),
      m_frames_passed(cooldown),
      m_game(game)
{
}

Bullet *Weapon::shoot()
{
    if (m_ammo > 0)
        --m_ammo;

    m_frames_passed = 0;
    return nullptr;
}

int Weapon::ammo() const
{
    return m_ammo;
}

bool Weapon::canShoot() const
{
    return m_cooldown == m_frames_passed && m_ammo != 0;
}

void Weapon::update()
{
    if (m_frames_passed < m_cooldown)
        ++m_frames_passed;
}

StandartWeapon::StandartWeapon(Game *game)
    : Weapon(game, -1, ResBag::get().weaponCooldown())
{

}

Bullet *StandartWeapon::shoot()
{
    if (!canShoot())
        return nullptr;
    Weapon::shoot();

    QRectF r = owner()->body()->boundingRect();
    QSizeF ratio = m_game->getRatioFromBoard();

    Physics* phys = new Physics(ResBag::get().bulletSpeed());
    Renderer* rend = new StaticRenderer(ResBag::get().bulletSprite(),
                                  ratio.width(), ratio.height(),
                                  m_game);
    rend->setZ(1);

    qreal bullet_w = ResBag::get().bulletSize();
    qreal bullet_h = ResBag::get().bulletSize();
    Body* body = new Body(r.center().x() - bullet_w/2,
                          r.center().y() - bullet_h/2,
                          ResBag::get().bulletSize(),
                          ResBag::get().bulletSize(),
                          owner()->body()->direction());
    switch(body->direction())
    {
    case Direction::UP:
        body->setPosition(body->x(), r.top() - body->height() ); break;
    case Direction::DOWN:
        body->setPosition(body->x(), r.bottom() ); break;
    case Direction::LEFT:
        body->setPosition(r.left() - body->width(), body->y()); break;
    case Direction::RIGHT:
        body->setPosition(r.right(), body->y()); break;
    }


    Bullet * bullet = new Bullet(body, rend, phys, m_owner, ResBag::get().bulletDamage());
    emit shot();
    return bullet;
}
