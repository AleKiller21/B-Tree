    #include "maintree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    maintree w;
    w.show();

    return a.exec();
}
