#ifndef Ball_H
#define Ball_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Ball : public QGraphicsItem
{
public:
    Ball();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setNumber(QString number);
    void setclicked();
    void setNotclicked();
    void setAngle(int angle);
    int  getAngle();
    int width,height;

protected:
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString numberSet;
    bool pressed;
};

#endif // Ball_H
