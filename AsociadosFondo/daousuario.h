#ifndef DAOUSUARIO_H
#define DAOUSUARIO_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOUsuario
{
public:
    DAOUsuario();
    ~DAOUsuario();
    QSqlDatabase* db;
    Connection* connection;
    void CrearUsuario(QString params[11]);
    void ActualizarUsuario(QString params[11]);
    QList<QString> ConsultarUsuario(QString cedula);
    bool ConsultarLogin(QString cedula, QString password);
};

#endif // DAOUSUARIO_H
