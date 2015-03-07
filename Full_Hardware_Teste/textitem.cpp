#include "textitem.h"

TextItem::TextItem()
{
    green = 0;
    setFlag(ItemIsSelectable);
}

QRectF TextItem::boundingRect() const
{
    return QRectF(0,0,25,25);
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font( "Newyork" );
    font.setPointSize(14);
    QPen myPen(QColor (255,128,0));

    if(green == 1)
    {
        myPen.setColor(Qt::green);
    }
    else if (green == 2)
    {
        myPen.setColor(Qt::yellow);
    }

    if(numberSet!="")
    {
        painter->setPen(myPen);
        painter->setFont(font);
        painter->drawText(15,10,numberSet);
    }
}

void TextItem::setNumber(QString number)
{
    numberSet = number;
}

void TextItem::setGreen()
{
    green = 1;
}

void TextItem::setYellow()
{
    green = 2;
}

void TextItem::setOrange()
{
    green = 0;
}
