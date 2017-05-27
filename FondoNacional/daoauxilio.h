#ifndef DAOAUXILIO_H
#define DAOAUXILIO_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOAuxilio
{
public:
    DAOAuxilio();
    ~DAOAuxilio();
    QSqlDatabase* db;
    Connection* connection;
    void CrearAuxilio(QString params[11]);
    void ActualizarEstado(QString referencia, QString estado, QString monto);
    QList<QList<QString>> ConsultarAuxilio(QString cedula);
    QList<QList<QString>> ConsultarAuxilio(QString fechaInicio, QString fechaFin, QString estado);
    double CuentaAuxilios();
};

#endif // DAOAUXILIO_H
