#include "itemimg.h"

ItemImg::ItemImg()
{
    tranparent= false;
    picture = ":/Imagem1.png";
    setFlag(ItemIsSelectable);
}

QRectF ItemImg::boundingRect() const
{
    return QRectF(0,0,25,25);
}

void ItemImg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath paht;
    paht.addEllipse(boundingRect());
    QBrush brush(Qt::transparent);
    QPixmap pic(picture);

    if(tranparent)
    {
        brush.setColor(Qt::transparent);
    }
    else
    {
        brush.setColor(Qt::gray);
    }

    painter->setBrush(brush);
    //painter->drawPath(paht);
    painter->drawPixmap(0,0,50,20,pic);
}

void ItemImg::setTransparent()
{
    tranparent = true;
}

void ItemImg::setVisible()
{
    tranparent = false;
}

void ItemImg::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    picture = ":/Imagem2.png";
    update();
    QGraphicsItem::mousePressEvent(event);
}

void ItemImg::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    picture = ":/Imagem1.png";
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
