#include "hat.h"

Hat::Hat()
{
    tranparent= false;
    setFlag(ItemIsSelectable);
}

QRectF Hat::boundingRect() const
{
    return QRectF(-7,-15,14,30);
}

void Hat::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static const QPointF points[7] = {
                QPointF(-5, -15),
                QPointF(-5, 5),
                QPointF(-7, 5),
                QPointF(0, 15),
                QPointF(7, 5),
                QPointF(5, 5),
                QPointF(5, -15)
            };

    QBrush brush(Qt::gray);
    QPen pen(Qt::black);
    QFont font( "Newyork" );
    font.setPointSize( 12 );

    if(tranparent)
    {
        brush.setColor(Qt::transparent);
        pen.setColor(Qt::transparent);
    }
    else
    {
        pen.setColor(Qt::black);
        brush.setColor(Qt::green);
    }

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(points,7);
}

void Hat::setTransparent()
{
    tranparent = true;
}

void Hat::setVisible()
{
    tranparent = false;
}

void Hat::advance(int phase)
{

}
