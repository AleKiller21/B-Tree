#include "maintree.h"
#include "ui_maintree.h"
#include <QDebug>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QInputDialog>
#include <QImage>
#include "BTree.h"
#include "dialog.h"
#include <QProcess>
BTree *tree;

int maintree::toMinDegree(int max)
{
    int t = (max+1)/2;
    return t;
}

maintree::maintree(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::maintree)
{
    ui->setupUi(this);
    int degree = toMinDegree(ui->comboBox->currentText().toInt());
    qDebug()<<"Tree with Min Degree: "<<degree;
    tree = new BTree(degree);
    scene = new TreeScene(this);
//    scene->setSceneRect(QRectF(0,0,5000,5000));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scale(1,1);
    ui->ScaleBox->setCurrentIndex(5);
    setWindowTitle("B-Tree");
    setUnifiedTitleAndToolBarOnMac(true);

}

maintree::~maintree()
{
    delete ui;
}

void maintree::print()
{
    scene->clear();
    tree->cross(scene);
    tree->height();
    scene->x = 2500;
    scene->y = 2500;
    int cont = 0;
}

void maintree::addToScene(QString value, int x, int y)
{
    qDebug()<<value;
    scene->setMode(TreeScene::InsertItem);
    scene->UpdateScene(value, x, y);

}

void maintree::on_comboBox_currentIndexChanged(int index)
{
    this->on_ClearBtn_clicked();

}

void maintree::on_AddButton_clicked()
{

    QString valor = ui->Value->text();
    int value;
    if(valor.isEmpty()){
        return;
    }
    if(valor.length() > 4)
    {
        QMessageBox msg;
        msg.setText("Input has to be greater than 4 digits");
        msg.exec();
        ui->Value->clear();
        this->print();
        return;
    }

    if(ui->Value->text().toInt() != 0){
        value = ui->Value->text().toInt();
    }else{
        value = 0;
        string x = ui->Value->text().toStdString();

        for(int i = 0; i<ui->Value->text().length() ; i++){
            value += x[i];
        }
    }
    tree->insert(value);
    this->print();

    ui->Value->clear();
}

void maintree::on_SearchButton_clicked()
{
        QMessageBox msg;
        if(ui->SearchValue->text().isEmpty()){
            msg.critical(this, "Error", "There's no input to search for!");
            return;
        }
        if(tree->search(ui->SearchValue->text().toInt()) != NULL){
            QList<QGraphicsItem*>items = scene->items();
            for(int i = 0; i<items.length() ; i++){
               if(items.at(i)->toolTip() == ui->SearchValue->text()){
                   items.at(i)->setOpacity(0.4);
                   msg.setText("The value "+ui->SearchValue->text()+" exists!");
                   msg.exec();
                   items.at(i)->setOpacity(1);
                   return;
               }
            }
            scene->update();

            return;
        }else{
            msg.setText("The value "+ui->SearchValue->text()+" doesn't exists!");
            msg.exec();
            return;
        }

}

void maintree::on_DeleteButton_clicked()
{

    tree->remove(ui->DeleteValue->text().toInt());
    this->print();

    ui->DeleteValue->clear();

}

void maintree::on_Value_returnPressed()
{
    this->on_AddButton_clicked();


}

void maintree::on_actionExample_triggered()
{


    QStringList its;
    its<<tr("Low")<<tr("Medium")<<tr("Hard")<<tr("Hardcore")<<tr("Insane");
    bool ok;
    QString option = QInputDialog::getItem(this, tr("Intensity"), tr("Choose your intensity: "), its, 0, false, &ok);
    if(!ok)
        return;
   else{
        this->on_ClearBtn_clicked();
        if(option == "Low"){
            for(int i = 0; i<15 ; i++){
                tree->insert(qrand()%100-1);
            }

            this->print();
        }else if(option == "Medium"){
            for(int i = 0; i<50 ; i++){
                tree->insert(qrand()%300-1);
            }
                QMatrix matrixold = ui->graphicsView->matrix();
                ui->graphicsView->resetMatrix();
                ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
                ui->graphicsView->scale(0.50,0.50);
                ui->ScaleBox->setCurrentIndex(3);
            this->print();

        }else if(option == "Hard"){
            for(int i = 0; i<300 ; i++){
                tree->insert(qrand()%2000-1);
            }
            QMatrix matrixold = ui->graphicsView->matrix();
            ui->graphicsView->resetMatrix();
            ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
            ui->graphicsView->scale(0.25,0.25);
            ui->ScaleBox->setCurrentIndex(2);
            this->print();
        }else if(option == "Hardcore"){
            for(int i = 0; i<2000 ; i++){
                tree->insert(qrand()%6000-1);
            }
            QMatrix matrixold = ui->graphicsView->matrix();
            ui->graphicsView->resetMatrix();
            ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
            ui->graphicsView->scale(0.12,0.12);
            ui->ScaleBox->setCurrentIndex(1);
            this->print();

        }else if(option == "Insane"){
            for(int i = 0; i<5000 ; i++){
                tree->insert(qrand()%8000000-1);
            }
            QMatrix matrixold = ui->graphicsView->matrix();
            ui->graphicsView->resetMatrix();
            ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
            ui->graphicsView->scale(0.05,0.05);
            ui->ScaleBox->setCurrentIndex(0);
            this->print();
        }

    }

}



void maintree::on_ScaleBox_activated(const QString &arg1)
{
    double nuevaescala = arg1.left(arg1.indexOf(tr("%"))).toDouble()/100.0;

    QMatrix matrixold = ui->graphicsView->matrix();
    ui->graphicsView->resetMatrix();
    ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
    ui->graphicsView->scale(nuevaescala,nuevaescala);
}

void maintree::on_ClearBtn_clicked()
{
    delete tree;
    int degree = toMinDegree(ui->comboBox->currentText().toInt());
    qDebug()<<"Tree with Min Degree: "<<degree;
    delete scene;
    scene = new TreeScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    QMatrix matrixold = ui->graphicsView->matrix();
    ui->graphicsView->resetMatrix();
    ui->graphicsView->translate(matrixold.dx(), matrixold.dy());
    ui->graphicsView->scale(1,1);
    ui->ScaleBox->setCurrentIndex(5);

    scene->clear();
    scene->update();

    tree = new BTree(degree);
}

void maintree::on_printBtn_clicked()
{
    BNode::nodeslist.clear();
    tree->save(scene);
    Dialog win;
    win.setModal(true);
    win.SetData(BNode::nodeslist);
    win.exec();

}

void maintree::on_actionSave_as_triggered()
{
    scene->clearSelection();
    scene->setSceneRect(scene->itemsBoundingRect());
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    scene->render(&painter);
    QString filename = QInputDialog::getText(this, tr("Save Image") , tr("Name: "), QLineEdit::Normal, "");
    if(filename == "")
        return;
    QStringList its;
    its<<tr(".png")<<tr(".jpg");
    bool ok;
    QString ext = QInputDialog::getItem(this, tr("Extension"), tr("Tipo de imagen: "), its, 0, false, &ok);
    if(!ok)
        return;
   else
    image.save(filename+ext);
}
