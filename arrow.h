#ifndef ARROW_H
#define ARROW_H
#include <QGraphicsLineItem>
#include "treeitem.h"
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Arrow : public QGraphicsLineItem
{
public:
    enum{Type = UserType +4};

    Arrow(TreeItem *startItem, TreeItem *endItem, QGraphicsItem *parent = 0);
    int type() const {return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color){myColor = color;}
    TreeItem *startItem() const {return myStartItem; }
    TreeItem *endItem() const {return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    TreeItem *myStartItem;
    TreeItem *myEndItem;
    QColor myColor;
    QPolygonF arrowHead;
};

#endif // ARROW_H
