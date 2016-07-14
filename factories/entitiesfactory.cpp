#include "entitiesfactory.h"

EntitiesFactory::EntitiesFactory(Game *rendererParent)
    : m_game(rendererParent),
      m_x_ratio(0),
      m_y_ratio(0),
      m_width(0),
      m_height(0)
{

}

void EntitiesFactory::setRatio(qreal x_ratio, qreal y_ratio)
{
    m_x_ratio = x_ratio;
    m_y_ratio = y_ratio;
}

void EntitiesFactory::setRatio(QSizeF ratio)
{
    setRatio(ratio.width(), ratio.height());
}

qreal EntitiesFactory::width() const
{
    return m_width;
}

qreal EntitiesFactory::height() const
{
    return m_height;
}


void EntitiesFactory::setSize(QSizeF size)
{
    m_width = size.width();
    m_height = size.height();
}

void EntitiesFactory::setSize(qreal size)
{
    m_width = m_height = size;
}
