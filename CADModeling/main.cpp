#include "CADModeling.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CADModeling w;
    w.show();
    return a.exec();
}
