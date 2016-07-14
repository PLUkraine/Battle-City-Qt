#ifndef ENTITIESFACTORY_H
#define ENTITIESFACTORY_H

#include "QQuickPaintedItem"
#include "game/game.h"

class Game;
class EntitiesFactory
{
public:
    EntitiesFactory(Game* rendererParent);
    void setRatio(qreal x_ratio, qreal y_ratio);
    void setRatio(QSizeF ratio);

    qreal width() const;
    qreal height() const;
    void setSize(QSizeF size);
    void setSize(qreal size);
protected:
    Game* m_game;
    qreal m_x_ratio, m_y_ratio;
    qreal m_width, m_height;
};

#endif // ENTITIESFACTORY_H
