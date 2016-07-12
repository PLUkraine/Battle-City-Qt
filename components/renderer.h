#ifndef RENDERER_H
#define RENDERER_H

#include <QQuickPaintedItem>

class Renderer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Renderer(QImage* image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem* parent=nullptr);
    void paint(QPainter *painter);

    void setRatio(const QSizeF& ratio);
public slots:
    void onUpdatePos(int x, int y);
    void onUpdateSize(int width, int height);
private:
    QImage* m_image;
    qreal m_x_tile_ratio;
    qreal m_y_tile_ratio;
};

#endif // RENDERER_H
