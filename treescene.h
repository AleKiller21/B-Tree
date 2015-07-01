#ifndef TREESCENE_H
#define TREESCENE_H
#include <QGraphicsScene>
#include "treeitem.h"
#include "nodoscene.h"

class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;

class TreeScene : public QGraphicsScene
{
public:
    int x;
    int y;

    enum Mode{ InsertItem, PrintItem, MoveItem };
    explicit TreeScene(QObject *parent = 0);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }

    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);
    void UpdateScene(QString valor, int x, int y);
    void Print(QString value, int x, int y);

public slots:
    void setMode(Mode mode);
    void setItemType(int t);
    void setDescription(QString description);

signals:
    void itemInserted(TreeItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);
    bool leftButtonDown;

    int itemType;

    Mode myMode;
    QString itemDesc;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

};

#endif // TREESCENE_H
