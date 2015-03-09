#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class BackButton : public QGraphicsItem
{
public:
    BackButton();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setNumber(QString number);
    void setclicked();
    void setNotclicked();

protected:
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString numberSet;
    bool pressed;
};

#endif // BACKBUTTON_H
