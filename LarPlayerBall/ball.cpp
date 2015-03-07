#include "Ball.h"

int AngleDirection2 = 0;

Ball::Ball()
{
    pressed = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    width=25;
    height=25;
}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath paht;
    paht.addEllipse(boundingRect());

    QBrush brush(Qt::gray);
    QFont font( "Newyork" );
    font.setPointSize( 10 );

    if(pressed)
    {
        brush.setColor(Qt::gray);
    }
    else
    {
        brush.setColor(QColor(255,102,0));
    }

    painter->setBrush(brush);
    painter->drawPath(paht);

    if(numberSet!="")
    {
        painter->setFont(font);
        painter->drawText(width/3,height/1.5,numberSet);
    }
}

void Ball::setNumber(QString number)
{
    numberSet = number;
}

void Ball::setclicked()
{
    pressed = true;
}

void Ball::setNotclicked()
{
    pressed = false;
}

void Ball::setAngle(int angle)
{
    AngleDirection2 = angle;
    update();
}

int Ball::getAngle()
{
    return AngleDirection2;
}

void Ball::advance(int phase)
{

}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
