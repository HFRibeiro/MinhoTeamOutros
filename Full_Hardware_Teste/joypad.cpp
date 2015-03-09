#include "joypad.h"

JoyPad::JoyPad()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF JoyPad::boundingRect() const
{
    return QRectF(0,0,35,35);
}

void JoyPad::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void JoyPad::setNumber(QString number)
{
    numberSet = number;
}

void JoyPad::setclicked()
{
    pressed = true;
}

void JoyPad::setNotclicked()
{
    pressed = false;
}

void JoyPad::advance(int phase)
{
    Q_UNUSED(phase);
}

void JoyPad::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void JoyPad::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    this->setPos(160,150);
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
