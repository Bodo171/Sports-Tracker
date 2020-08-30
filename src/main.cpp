#include "SportManager.h"
#include <QtWidgets/QApplication>
///to do:
///sport GUI (nem)
///observer?
///error handler?
///sports backend (done)
///undo?
///database
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SportManager w;
    w.show();
    return a.exec();
}
