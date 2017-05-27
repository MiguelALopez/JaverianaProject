#ifndef DAOAHORRO_H
#define DAOAHORRO_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOAhorro
{
public:
    DAOAhorro();
    ~DAOAhorro();
    QSqlDatabase* db;
    Connection* connection;
    void CrearAhorro(QString params[3]);
    QList<QList<QString>> ConsultarAhorro(QString cedula);
    QList<QList<QString>> ConsultarAhorro(QString fechaInicio, QString fechaFin);
};

#endif // DAOAHORRO_H
