#include "myitem.h"

MyItem::MyItem()
{
    pressed = false;
    setFlag(ItemIsSelectable);
}

QRectF MyItem::boundingRect() const
{
    return QRectF(0,0,25,25);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //QRectF rec = boundingRect();

    QPainterPath paht;
    paht.addEllipse(boundingRect());
    QBrush brush(Qt::gray);
    QFont font( "Newyork" );
    font.setPointSize( 12 );

    if(pressed)
    {
        brush.setColor(Qt::green);
    }
    else
    {
        brush.setColor(Qt::gray);
    }

    painter->setBrush(brush);
    painter->drawPath(paht);

    if(numberSet!="")
    {
        painter->setFont(font);
        painter->drawText(7,19,numberSet);
    }
}

void MyItem::setNumber(QString number)
{
    numberSet = number;
}

void MyItem::setclicked()
{
    pressed = true;
}

void MyItem::setNotclicked()
{
    pressed = false;
}

void MyItem::advance(int phase)
{
    Q_UNUSED(phase);
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
