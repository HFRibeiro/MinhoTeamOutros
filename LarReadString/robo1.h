#ifndef ROBO1_H
#define ROBO1_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Robo1 : public QGraphicsItem
{
public:
    Robo1();
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

#endif // ROBO1_H
