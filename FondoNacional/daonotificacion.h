#ifndef DAONOTIFICACION_H
#define DAONOTIFICACION_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAONotificacion
{
public:
    DAONotificacion();
    ~DAONotificacion();
    QSqlDatabase* db;
    Connection* connection;
    void CrearNotificacion(QString params[4]);
    QList<QList<QString>> ConsultarNotificacion(QString cedula);
};

#endif // DAONOTIFICACION_H
