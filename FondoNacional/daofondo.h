#ifndef DAOFONDO_H
#define DAOFONDO_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOFondo
{
public:
    DAOFondo();
    ~DAOFondo();
    QSqlDatabase* db;
    Connection* connection;
    void ActualizarFondo(QString params[2]);
    QList<QString> ConsultarFondo();
    void ActualizarPropiedadesAhorro(QString params[2]);
    QList<QString> ConsultarPropiedadesAhorro();
    void ActualizarPropiedadesCredito(QString params[7]);
    QList<QString> ConsultarPropiedadesCredito();
    void ActualizarPropiedadesAuxilio(QString params[4]);
    QList<QString> ConsultarPropiedadesAuxilio();
};

#endif // DAOFONDO_H
