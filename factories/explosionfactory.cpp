#include "explosionfactory.h"
#include "utils/resoursecontainer.h"

ExplosionFactory::ExplosionFactory(Game *game)
    : EntitiesFactory(game)
{

}

Explosion *ExplosionFactory::createExplosion(qreal x, qreal y)
{
    const int frames = 5;

    Body *body = new Body(x, y, m_width, m_height, Direction::UP);
    Renderer* renderer = new AnimationRenderer(
                ResBag::get().explosionSprite(),
                frames,
                ResBag::get().explosionDuration()/frames,
                m_x_ratio,
                m_y_ratio,
                m_game
                );
    Explosion* expl = new Explosion(renderer, body, ResBag::get().explosionDuration());
    return expl;
}
