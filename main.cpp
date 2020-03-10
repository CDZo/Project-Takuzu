#include "presenter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    presenter w;
    w.show();

    return a.exec();
}
