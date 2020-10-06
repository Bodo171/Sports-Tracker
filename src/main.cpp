#include "SportManager.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SportManager w;
    w.show();
    return a.exec();
}
