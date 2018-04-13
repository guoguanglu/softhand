#include "softroboticwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    softroboticWidget w;
    w.show();

    return a.exec();
}
