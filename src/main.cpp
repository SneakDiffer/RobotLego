#include "ui/qapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApp w;
    w.show();

    return a.exec();

}
