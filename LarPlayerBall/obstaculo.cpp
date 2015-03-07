#include "Obstaculo.h"
#include <QDebug>
#include "math.h"

int AngleDirection3 = 0;

Obstaculo::Obstaculo()
{
    pressed = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    width=25;
    height=25;
}

QRectF Obstaculo::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Obstaculo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
        brush.setColor(QColor(0,0,0));
    }

    painter->setBrush(brush);
    painter->drawPath(paht);

    if(numberSet!="")
    {
        painter->setFont(font);
        painter->drawText(width/3,height/1.5,numberSet);
    }
}

void Obstaculo::setNumber(QString number)
{
    numberSet = number;
}

void Obstaculo::setclicked()
{
    pressed = true;
}

void Obstaculo::setNotclicked()
{
    pressed = false;
}

void Obstaculo::setAngle(int angle)
{
    AngleDirection3 = angle;
    update();
}

int Obstaculo::getAngle()
{
    return AngleDirection3;
}

bool Obstaculo::setSize(float distance[])
{
    float size = 0;
    float tanmesure = tan(5* (M_PI / 180.0));
    for(int k =0;k<72;k++)
    {
        if(distance[k]!=0)
        {
            size += tanmesure*distance[k];
        }

    }
    //qDebug() << size * 80;
    width = size * 80;
    height = size * 80;
}

void Obstaculo::advance(int phase)
{

}

void Obstaculo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Obstaculo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
