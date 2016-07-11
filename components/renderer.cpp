#include<QPainter>
#include<QDebug>

#include "renderer.h"

Renderer::Renderer(QImage *image, QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_image(image)
{
}

void Renderer::paint(QPainter *painter)
{
    painter->drawImage(this->boundingRect(), *m_image);
}

void Renderer::onUpdatePos(qreal x, qreal y)
{
    this->setPosition(QPointF(x, y));
    update();
}
