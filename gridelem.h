#ifndef GRIDELEM_H
#define GRIDELEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QFile>

class gridElem : public QObject, public QGraphicsItem
{
    Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int _size;
    int _x, _y;
    int _type;
    int _type_n;
    bool _pressed;
public:
    explicit gridElem(QObject *parent = 0,int size = 20,int type=0,int type_n=0);
    void moveTo(int x, int y);
    void setType(int n);
    void setPressed(bool a);
    bool isPressed();
    ~gridElem();
signals:
    void signal1(int x, int y, int type);//emit when pressed

};

#endif // GRIDELEM_H
