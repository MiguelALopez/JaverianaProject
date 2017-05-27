#ifndef DAOFAQ_H
#define DAOFAQ_H

#include "connection.h"
#include <QtSql>
#include <QString>
#include <QDebug>

class DAOFaq
{
public:
    DAOFaq();
    ~DAOFaq();
    QSqlDatabase* db;
    Connection* connection;
    void CrearFaq(QString params[3]);
    void ActualizarFaq(QString referencia, QString descripcion, QString estado);
    QList<QList<QString>> ConsultarFaq(QString estado);
    QList<QList<QString>> ConsultarFaq();
};

#endif // DAOFAQ_H
