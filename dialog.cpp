#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new TreeScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scale(1,1);
    setWindowFlags(Qt::Window);
    setWindowTitle("B-Tree Items");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetData(QList<int> data)
{
    NodoScene* node;
    int x = 0;
    for(int i = 0; i<data.length() ; i++){
//        scene->addEllipse(x, 0, 35,35, QPen(Qt::white), QBrush(Qt::green));
//         scene->addText(QString::number(data.at(i)), QFont("Fantasy"))->setPos(x, 0);
        node = new NodoScene(QString::number(data.at(i)), true, x, 0);
        scene->addItem(node);
        x+=35;

    }
}
