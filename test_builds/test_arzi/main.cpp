#include "arzi.h"
#include "zipreader.h"
#include "zipwriter.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arzi w;
    w.show();



    return a.exec();
}
