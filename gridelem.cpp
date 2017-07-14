#include "gridelem.h"
#include "QDebug"
gridElem::gridElem(QObject *parent,int size,int type,int n)
    : QObject(parent), QGraphicsItem(){
    _size=size;
    _type=type;
    _type_n=n;
    _pressed=false;
}

void gridElem::moveTo(int x, int y)
{
    _x=x;
    _y=y;
}

gridElem::~gridElem(){
}

void gridElem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
    if(event->buttons() & Qt::LeftButton){
        event->accept();
        _pressed=true;
        update();
        emit signal1(_x,_y,_type);

        QGraphicsItem::mousePressEvent(event);
    }
}

QRectF gridElem::boundingRect() const
{
    return QRectF(0,0,_size,_size);
}

void gridElem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    QColor fillC;
    fillC.setHsv(0,0,12);
    painter->setBrush(fillC);
    painter->setPen(fillC);
    painter->drawRect(0,0,_size,_size);
    QColor test1;
    QRadialGradient gr1;
    QRadialGradient shadow;
    switch (_type) {
    case -1:
        fillC.setHsv(110,50,135);
        painter->setBrush(fillC);
        painter->setPen(fillC);
        painter->drawRect(1,1,_size-2,_size-2);
        break;
        break;
    case 0:
        fillC.setHsv(0,0,135);
        painter->setBrush(fillC);
        painter->setPen(fillC);
        painter->drawRect(1,1,_size-2,_size-2);
        break;
    default:
        if(_pressed){
            fillC.setHsv(0,0,165);
        }else{
            fillC.setHsv(0,0,135);
        }
        painter->setBrush(fillC);
        painter->setPen(fillC);
        painter->drawRect(1,1,_size-2,_size-2);
        int t=(359/_type_n)*_type;
        test1.setHsv(t,255,125);

        QPointF center;
        QPointF focal;
        painter->setPen(fillC);
        center.setX((double)_size/2+1);
        center.setY((double)_size/2+1);
        focal.setX((double)_size/2+5);
        focal.setY((double)_size/2+9);
        shadow.setCenter(center);
        shadow.setFocalPoint(focal);
        shadow.setRadius(18);
        shadow.setColorAt(1.0,fillC);
        shadow.setColorAt(0.57,Qt::black);
        shadow.setColorAt(0.0,Qt::black);
        painter->setBrush(shadow);
        painter->drawEllipse(center,18,18);
        focal.setX((double)_size/2-3);
        focal.setY((double)_size/2-6);
        center.setX((double)_size/2);
        center.setY((double)_size/2);
        painter->setPen(test1);
        gr1.setCenter(center);
        gr1.setFocalPoint(focal);
        gr1.setRadius(15);
        gr1.setColorAt(0.99,test1);
        gr1.setColorAt(1.0,Qt::black);
        gr1.setColorAt(0.0,Qt::white);
        painter->setBrush(gr1);

        painter->drawEllipse(center,15,15);
        break;
    }
    _pressed=false;
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void gridElem::setType(int n)
{
    _type=n;
}

void gridElem::setPressed(bool a)
{
    _pressed=a;
}

bool gridElem::isPressed()
{
    return _pressed;
}
