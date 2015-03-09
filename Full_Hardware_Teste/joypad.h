#ifndef JOYPAD_H
#define JOYPAD_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class JoyPad : public QGraphicsItem
{
public:
    JoyPad();
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

#endif // JOYPAD_H
