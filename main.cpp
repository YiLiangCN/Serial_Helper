#include "Serial_Helper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Serial_Helper w;
    w.show();
    return a.exec();
}
