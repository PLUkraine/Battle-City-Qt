#ifndef RENDERER_H
#define RENDERER_H

#include <QQuickPaintedItem>

class Renderer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Renderer(QImage* image, QQuickItem* parent=nullptr);
    void paint(QPainter *painter);
public slots:
    void onUpdatePos(qreal x, qreal y);
private:
    QImage* m_image;
};

#endif // RENDERER_H
