#include "arzi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arzi w;
    w.show();
    return a.exec();
}
