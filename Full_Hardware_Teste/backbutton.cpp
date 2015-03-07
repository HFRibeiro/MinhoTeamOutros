#include "backbutton.h"

BackButton::BackButton()
{
    pressed = false;
    setFlag(ItemIsSelectable);
}

QRectF BackButton::boundingRect() const
{
    return QRectF(0,0,35,11);
}

void BackButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    /*QPainterPath paht;
    paht.addEllipse(boundingRect());*/
    QBrush brush(Qt::red);
    QFont font( "Newyork" );
    font.setPointSize( 9 );

    if(pressed)
    {
        brush.setColor(Qt::green);
    }
    else
    {
        brush.setColor(QColor (180,180,180));
    }
    //QPainterPath path;
    //path.moveTo(0, 0);
    /*path.cubicTo(20, -10,  30, 10,  40, 10);
    path.moveTo(0, 20);
    path.cubicTo(10, 30,  0, 10,  40, 10);*/
    //path.cubicTo(0,9,  5, 5,  0, 0);

    /*path.moveTo(0, 0);
    path.cubicTo(99, 0,  50, 50,  99, 99);
    path.cubicTo(0, 99,  50, 50,  0, 0);*/
    QPen myPen(QColor (180,180,180));
    painter->setPen(myPen);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);

    /*painter->setBrush(brush);
    painter->drawPath(path);*/

    if(numberSet!="")
    {
        QPen myPen2(Qt::black);
        painter->setPen(myPen2);
        painter->setFont(font);
        painter->drawText(15,10,numberSet);
    }
}

void BackButton::setNumber(QString number)
{
    numberSet = number;
}

void BackButton::setclicked()
{
    pressed = true;
}

void BackButton::setNotclicked()
{
    pressed = false;
}

void BackButton::advance(int phase)
{

}

void BackButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void BackButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
