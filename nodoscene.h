#ifndef NODOSCENE
#define NODOSCENE

#include <QGraphicsItem>
#include <QPainter>
#include "arrow.h"

class NodoScene : public QGraphicsItem
{
private:
    //QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow*> arrows;

public:
    enum { Type = UserType+15};

    QString description;
    bool pressed;
    int mytype;
    int type(){ return Type;}
    int posSceneX;
    int posSceneY;
    bool print;

    NodoScene(QString description, bool print, int sceneX = 2500, int sceneY = 2500)
    {
        this->description = description;
        this->posSceneX = sceneX;
        this->posSceneY = sceneY;
        this->print = print;
    }


    QRectF boundingRect() const
    {
        return QRectF(posSceneX, posSceneY, 35, 35);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {

        QBrush brush(Qt::darkGreen);
        QRectF rect = boundingRect();
        if(print){
            brush.setColor(Qt::blue);
        }
        painter->fillRect(rect, brush);
        painter->drawRect(rect);
        painter->setFont(QFont("Fantasy", 9, QFont::Bold));
        painter->setPen(Qt::white);
        setToolTip(description);
        painter->drawText(rect, description,QTextOption(Qt::AlignCenter));

        //painter->drawText(posSceneX, posSceneY, 30, 60, 0, description);
    }

    void removeArrow(Arrow *arrow)
    {

    }

    void removeArrows()
    {

    }

    void addArrow(Arrow *arrow)
    {

    }

    QPixmap image() const
    {

    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {

    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsItem::mousePressEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {

        QGraphicsItem::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {


        QGraphicsItem::mouseMoveEvent(event);

    }
};

#endif // NODOSCENE

