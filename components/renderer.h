#ifndef RENDERER_H
#define RENDERER_H

#include <QQuickPaintedItem>

enum class Direction;
class Renderer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Renderer(QImage* image, qreal x_tile_ratio, qreal y_tile_ratio, int rows, int cols, QQuickItem* parent);
    void paint(QPainter *painter);

    void setRatio(const QSizeF& ratio);
public slots:
    virtual void onUpdatePos(qreal x, qreal y);
    virtual void onUpdateSize(qreal width, qreal height);
    virtual void onUpdateDirection(Direction)=0;
protected:
    void setPart(int row, int col);

    QImage* m_image;
    qreal m_x_tile_ratio;
    qreal m_y_tile_ratio;

    // for future classes
    int m_rows, m_cols, m_column, m_row;
};

class StaticRenderer : public Renderer
{
    Q_OBJECT
public:
    StaticRenderer(QImage* image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem* parent);
public slots:
    void onUpdateDirection(Direction) {}
};

class DirectionRenderer : public Renderer
{
    Q_OBJECT
public:
    DirectionRenderer(QImage* image, qreal x_tile_ratio, qreal y_tile_ratio, QQuickItem* parent);
public slots:
    void onUpdateDirection(Direction);
};

#endif // RENDERER_H
