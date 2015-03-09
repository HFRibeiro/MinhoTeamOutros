#ifndef HAT_H
#define HAT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Hat : public QGraphicsItem
{
public:
    Hat();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTransparent();
    void setVisible();

protected:
    void advance(int phase);

private:
    bool tranparent;
};

#endif // HAT_H
