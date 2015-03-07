#include "robo1.h"
#include <QDebug>

int AngleDirection1 = 0;

Robo1::Robo1(MainWindow *mainw)
{
    pressed = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsScenePositionChanges);
    width=40;
    height=40;
    myMain = mainw;
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

void Robo1::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    if(myMain->OnMove)
    {
        qDebug() << "Start: " << this->pos();
        x1 = this->pos().x()+width/2;
        y1 = this->pos().y()+height/2;
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Robo1::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    if(myMain->OnMove)
    {
        x2 = this->pos().x()+width/2;
        y2 = this->pos().y()+height/2;
        myMain->drawLine(x1,y1,x2,y2);
        qDebug() << "Stopt: " << this->pos();
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Robo1::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(myMain->OnMove)
    QGraphicsItem::mouseMoveEvent(event);
}

QVariant Robo1::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
            // value is the new position.
            QPointF newPos = value.toPointF();
            QRectF rect = scene()->sceneRect();
            rect.setX(rect.x()-(width/2));
            rect.setWidth(rect.width()-(width/2));
            rect.setY(rect.y()-(height/2)+2);
            rect.setHeight(rect.height()-(height/2)-2);

            if (!rect.contains(newPos)) {
                // Keep the item inside the scene rect.
                newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
                newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
                return newPos;
            }
        }
    return QGraphicsItem::itemChange(change, value);
}
