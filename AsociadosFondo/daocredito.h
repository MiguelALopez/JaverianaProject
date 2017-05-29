#ifndef DAOCREDITO_H
#define DAOCREDITO_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOCredito
{
public:
    DAOCredito();
    ~DAOCredito();
    QSqlDatabase* db;
    Connection* connection;
    void CrearCredito(QString params[11]);
    QList<QString> ConsultarUsuario(QString cedula);
    bool ConsultarLogin(QString cedula, QString password);
    void ActualizarEstado(QString referencia, QString estado, QString valor);
    QList<QList<QString>> ConsultarCredito(QString cedula);
    QList<QList<QString>> ConsultarCredito(QString fechaInicio, QString fechaFin, QString estado);
};

#endif // DAOCREDITO_H
