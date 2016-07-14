#include "tankfactory.h"

TankFactory::TankFactory(Game *game)
    : EntitiesFactory(game)
{
    setSize(ResBag::get().tankSize());
}

Tank* TankFactory::createTank(qreal x, qreal y)
{
    Body* body = new Body(x, y, m_width, m_height, Direction::UP);
    Weapon* weapon = new StandartWeapon(m_game);
    Health* health = new Health(ResBag::get().tankHealth());
    Physics* physics = new Physics(ResBag::get().tankSpeed());
    Renderer* renderer = new DirectionRenderer(ResBag::get().tankSprite(),
                                               m_x_ratio, m_y_ratio,
                                               m_game);
    Tank* tank = new Tank(body, renderer, physics, health, weapon);
    return tank;
}

Tank *TankFactory::createPlayerTank(qreal x, qreal y)
{
    Body* body = new Body(x, y, m_width, m_height, Direction::UP);
    Weapon* weapon = new StandartWeapon(m_game);
    Health* health = new Health(ResBag::get().playerTankHealth());
    Physics* physics = new Physics(ResBag::get().tankSpeed());
    Renderer* renderer = new DirectionRenderer(ResBag::get().playerTankSprite(),
                                               m_x_ratio, m_y_ratio,
                                               m_game);
    Tank* tank = new Tank(body, renderer, physics, health, weapon);
    return tank;
}
