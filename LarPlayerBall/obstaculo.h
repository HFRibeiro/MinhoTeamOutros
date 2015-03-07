#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Obstaculo : public QGraphicsItem
{
public:
    Obstaculo();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setNumber(QString number);
    void setclicked();
    void setNotclicked();
    void setAngle(int angle);
    int  getAngle();
    int width,height;
    bool setSize(float distance[72]);

protected:
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString numberSet;
    bool pressed;
};

#endif // Obstaculo_H
