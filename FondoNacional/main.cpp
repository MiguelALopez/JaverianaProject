#include "fondotrabajadores.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FondoTrabajadores w;
    w.show();

    return a.exec();
}
