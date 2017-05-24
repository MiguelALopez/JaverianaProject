#include "asociadosfondo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AsociadosFondo w;
    w.show();

    return a.exec();
}
