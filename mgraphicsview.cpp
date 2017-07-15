#include "mgraphicsview.h"

mGraphicsView::mGraphicsView(QWidget *parent):QGraphicsView()
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void mGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = qPow(2.0, event->delta() / 440.0);
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if(0.05 < factor && factor < 10) scale(scaleFactor, scaleFactor);
}

void mGraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() == Qt::RightButton)
    {
        QPointF oldp = mapToScene(m_originX, m_originY);
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x(), translation.y());

        m_originX = event->x();
        m_originY = event->y();
    }
}

void mGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_originX = event->x();
        m_originY = event->y();
    }
    QGraphicsView::mousePressEvent(event);
}


