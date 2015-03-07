#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class TextItem : public QGraphicsItem
{
public:
    TextItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setNumber(QString number);
    void setGreen();
    void setOrange();
    void setYellow();

protected:

private:
    QString numberSet;
    int green;
};

#endif // TEXTITEM_H
