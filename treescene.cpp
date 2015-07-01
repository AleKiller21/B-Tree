#include "treescene.h"
#include <QDebug>
TreeScene::TreeScene(QObject *parent) : QGraphicsScene(parent)
{
    myMode = MoveItem;
    itemType = 0;
    line = 0;
    myItemColor = Qt::darkGreen;
    myTextColor = Qt::white;
    myLineColor = Qt::black;
    x = 2500;
    y = 2500;


}

void TreeScene::setLineColor(const QColor &color)
{

}

void TreeScene::setTextColor(const QColor &color)
{

}

void TreeScene::setItemColor(const QColor &color)
{

}

void TreeScene::setFont(const QFont &font)
{

}

void TreeScene::UpdateScene(QString valor, int x, int y)
{

        //TreeItem*item;
        switch(myMode){
                 case InsertItem:
//                        item = new TreeItem("5");
//                        item->setPos(2500,2500);
//                        addItem(item);
                NodoScene* nodo = new NodoScene(valor, false, x, y);
                addItem(nodo);

                //addRect(2500, 2500, 100, 100);
                        break;
        }

}

void TreeScene::Print(QString value, int x, int y)
{
   addText(value, QFont("Monospace"))->setPos(x, y);

}

void TreeScene::setMode(TreeScene::Mode mode)
{
    myMode = mode;
}

void TreeScene::setItemType(int t)
{
    itemType = t;
}

void TreeScene::setDescription(QString description)
{
    itemDesc = description;
}

void TreeScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void TreeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void TreeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

bool TreeScene::isItemChange(int type)
{

}
