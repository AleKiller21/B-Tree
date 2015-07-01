#ifndef TREEITEM_H
#define TREEITEM_H
#include <QGraphicsPixmapItem>
#include <QList>
class QPixmap;
//class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
//class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;

class Arrow;

class TreeItem : public QGraphicsItem//,public QGraphicsPolygonItem
{
public:
    enum { Type = UserType+15};

    TreeItem(QString description/*,QGraphicsItem *parent = 0*/);

    QString description;
    bool pressed;
    int mytype;
    void removeArrow(Arrow *arrow);
    void removeArrows();
    QPolygonF polygon() const;
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type(){ return Type;}

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;

};


#endif // TREEITEM_H
