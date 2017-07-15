#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QGraphicsView>
#include <qmath.h>
#include <QWheelEvent>
#include <QMouseEvent>

class mGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    mGraphicsView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
private:
    qreal m_originX,m_originY;
};

#endif // MGRAPHICSVIEW_H
