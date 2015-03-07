#ifndef ROBO1_H
#define ROBO1_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "mainwindow.h"

class Robo1 : public QGraphicsItem
{
public:
    Robo1(MainWindow *mainw);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setNumber(QString number);
    void setclicked();
    void setNotclicked();
    void setAngle(int angle);
    int  getAngle();
    int width,height;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString numberSet;
    bool pressed;
    MainWindow *myMain;
    int x1,x2,y1,y2;
};

#endif // ROBO1_H
