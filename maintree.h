#ifndef MAINTREE_H
#define MAINTREE_H
#include <QMainWindow>
#include <QTimeLine>
#include "treescene.h"
namespace Ui {
class maintree;
}

class maintree : public QMainWindow
{
    Q_OBJECT

public:
    int toMinDegree(int max);
    explicit maintree(QWidget *parent = 0);
    ~maintree();
    TreeScene *scene;
    void print();
    void addToScene(QString value, int x, int y);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_AddButton_clicked();

    void on_SearchButton_clicked();

    void on_DeleteButton_clicked();

    void on_Value_returnPressed();

    void on_actionExample_triggered();


    void on_ScaleBox_activated(const QString &arg1);

    void on_ClearBtn_clicked();

    void on_printBtn_clicked();

    void on_actionSave_as_triggered();

private:
    Ui::maintree *ui;
};




#endif // MAINTREE_H
