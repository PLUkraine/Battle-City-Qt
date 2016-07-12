#include<QPainter>
#include<QDebug>

#include "renderer.h"

Renderer::Renderer(QImage *image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_image(image),
      m_x_tile_ratio(x_tile_ratio),
      m_y_tile_ratio(y_tile_ratio)
{
}

void Renderer::paint(QPainter *painter)
{
    painter->drawImage(this->boundingRect(), *m_image);
}

void Renderer::setRatio(const QSizeF &ratio)
{
    // must recompute all coordinates for new positions
    qreal height_r = ratio.height() / m_y_tile_ratio;
    qreal width_r = ratio.width() / m_x_tile_ratio;

    setPosition(QPointF(x()*width_r, y()*height_r));
    setSize(QSizeF(width()*width_r, height()*height_r));

    m_x_tile_ratio = ratio.width();
    m_y_tile_ratio = ratio.height();

    update();
}

void Renderer::onUpdatePos(int x, int y)
{
    this->setPosition(QPointF(x*m_x_tile_ratio, y*m_y_tile_ratio));
    update();
}

void Renderer::onUpdateSize(int width, int height)
{
    this->setSize(QSizeF(width*m_x_tile_ratio, height*m_y_tile_ratio));
    update();
}
