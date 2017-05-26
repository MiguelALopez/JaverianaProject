#include "asociadosfondo.h"
#include "login.h"
#include "daousuario.h"
#include "daofondo.h"
#include <QApplication>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
//    DAOUsuario daousuario;

//    //Create usuario
//    QString params[11] = {"1263", "abc", "Nestor", "Trin", "1997-11-30", "113515", "cra 12", "Masculino", "Casado", "juan@gmail.com", "1000000"};
//    daousuario.CrearUsuario(params);

//    //Read usuario
//    QString cedula = "1263";
//    QList<QString> consulta = daousuario.ConsultarUsuario(cedula);
//    for (int i=0; i<11; i++){
//        qDebug() << consulta[i];
//    }

//    //Update usuario
//    QString params2[11] = {"1263", "abc", "Nestor", "Trin", "2004-11-30", "113515", "cra 21", "Masculino", "Viudo", "juan@caliescali.com", "500000"};
//    daousuario.ActualizarUsuario(params2);

//    //Read again usuario
//    consulta = daousuario.ConsultarUsuario(cedula);
//    for (int i=0; i<11; i++){
//        qDebug() << consulta[i];
//    }

//    //Sucessfull login attempt
//    bool login = daousuario.ConsultarLogin("1263", "abc");
//    qDebug() << "Login attempt: " << login;

//    //Failed login attempt
//    login = daousuario.ConsultarLogin("1263", "helado");
//    qDebug() << "Login attempt: " << login;

    DAOFondo daofondo;
    QList<QString> consulta = daofondo.ConsultarPropiedadesAhorro();
    QList<QString> fondo = daofondo.ConsultarFondo();

    QApplication a(argc, argv);
//    AsociadosFondo w;
//    w.show();
    Login l;
    l.show();


    return a.exec();
}
