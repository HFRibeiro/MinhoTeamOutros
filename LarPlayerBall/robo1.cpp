#include "robo1.h"
#include <QDebug>

int AngleDirection1 = 0;

Robo1::Robo1()
{
    pressed = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    width=40;
    height=40;
}

QRectF Robo1::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Robo1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath ellipsePath;
    ellipsePath.moveTo(width/2,height/2);
    ellipsePath.arcTo(boundingRect(), AngleDirection1+30, 300);

    QBrush brush(Qt::gray);
    QFont font( "Newyork" );
    font.setPointSize( 14 );

    if(pressed)
    {
        brush.setColor(Qt::gray);
    }
    else
    {
        brush.setColor(Qt::blue);
    }

    painter->setBrush(brush);
    painter->drawPath(ellipsePath);

    if(numberSet!="")
    {
        painter->setFont(font);
        painter->drawText(width/4,height/1.8,numberSet);
    }
}

void Robo1::setNumber(QString number)
{
    numberSet = number;
}

void Robo1::setclicked()
{
    pressed = true;
}

void Robo1::setNotclicked()
{
    pressed = false;
}

void Robo1::setAngle(int angle)
{
    AngleDirection1 = angle;
    update();
}

int Robo1::getAngle()
{
    return AngleDirection1;
}

void Robo1::advance(int phase)
{

}

void Robo1::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Robo1::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    //qDebug() << this->pos();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
