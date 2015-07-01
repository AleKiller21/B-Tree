#include "treeitem.h"
//#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>

TreeItem::TreeItem(QString description) //: QGraphicsPolygonItem(parent)
{
    this->description = description;

//    myPolygon << QPointF(-25, -25) << QPointF(25, -25)
//              << QPointF(25, 25) << QPointF(-25, 25)
//              << QPointF(-25, -25);
//    setPolygon(myPolygon);
}

void TreeItem::removeArrow(Arrow *arrow)
{

}

void TreeItem::removeArrows()
{

}

QPolygonF TreeItem::polygon() const
{

}

void TreeItem::addArrow(Arrow *arrow)
{

}

QPixmap TreeItem::image() const
{

}

void TreeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

//QVariant TreeItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{

//}

void TreeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void TreeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mouseReleaseEvent(event);
}

void TreeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    QGraphicsItem::mouseMoveEvent(event);

}

void TreeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

//    QBrush brush(Qt::darkGreen);
    qDebug()<<"HOLII!";
//    painter->setBrush(brush);
//    painter->setPen(Qt::black);
//    painter->drawPolygon(myPolygon);
//    painter->drawRect(0, 0, 100, 100);
//    painter->setPen(Qt::white);
//    painter->drawText(-4,5,this->description);

    QBrush brush(Qt::red);
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
    painter->setFont(QFont("Fantasy", 12, QFont::Bold));
    painter->drawText(rect, "hola");

}

QRectF TreeItem::boundingRect() const
{
    return QRectF(2500, 2500, 100, 100);
}
