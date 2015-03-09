#ifndef ITEMIMG_H
#define ITEMIMG_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>

class ItemImg : public QGraphicsItem
{
public:
    ItemImg();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTransparent();
    void setVisible();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool tranparent;
    QString picture;
};

#endif // ITEMIMG_H
