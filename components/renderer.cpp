#include<QPainter>
#include<QDebug>

#include "renderer.h"
#include "body.h"

Renderer::Renderer(QImage *image, qreal x_tile_ratio, qreal y_tile_ratio, int rows, int cols, QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_image(image),
      m_x_tile_ratio(x_tile_ratio),
      m_y_tile_ratio(y_tile_ratio),
      m_rows(rows),
      m_cols(cols),
      m_column(0),
      m_row(0)
{
}

void Renderer::paint(QPainter *painter)
{
    qreal sprite_width = m_image->width() / m_cols;
    qreal sprite_height = m_image->height() / m_rows;
    QRectF source(sprite_width * m_column,
                  sprite_height * m_row,
                  sprite_width,
                  sprite_height
                  );
    painter->drawImage(this->boundingRect(), *m_image, source);
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

void Renderer::onUpdatePos(qreal x, qreal y)
{
    //qDebug() << "NEW POS" << x << y;
    this->setPosition(QPointF(x*m_x_tile_ratio, y*m_y_tile_ratio));
    qobject_cast<QQuickPaintedItem *>(parent())->update();
}

void Renderer::onUpdateSize(qreal width, qreal height)
{
    this->setSize(QSizeF(width*m_x_tile_ratio, height*m_y_tile_ratio));
    qobject_cast<QQuickPaintedItem *>(parent())->update();
}

void Renderer::setPart(int row, int col)
{
    m_row = row;
    m_column = col;
    update();
}



StaticRenderer::StaticRenderer(QImage *image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem *parent)
    : Renderer(image, x_tile_ratio, y_tile_ratio, 1, 1, parent)
{
}

DirectionRenderer::DirectionRenderer(QImage *image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem *parent)
    : Renderer(image, x_tile_ratio, y_tile_ratio, 4, 1, parent)
{
}

void DirectionRenderer::onUpdateDirection(Direction dir)
{
    m_row = (int)dir;
    update();
}

AnimationRenderer::AnimationRenderer(QImage *image, int frames, int delay, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem *parent)
    : Renderer(image, x_tile_ratio, y_tile_ratio, frames, 1, parent),
      m_delay(delay)
{
}

void AnimationRenderer::onUpdateTime(int lifetime)
{
    if (lifetime % m_delay == 0) {
        m_row = (m_row + 1) % m_rows;
        update();
    }
}
