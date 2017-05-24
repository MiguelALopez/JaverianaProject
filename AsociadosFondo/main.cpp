#include "asociadosfondo.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    AsociadosFondo w;
//    w.show();
    Login l;
    l.show();

    return a.exec();
}
