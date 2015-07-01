#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QList>
#include "treescene.h"
using namespace std;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT


public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    TreeScene* scene;
    void SetData(QList<int> data);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
