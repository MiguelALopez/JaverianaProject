#include "daoahorro.h"

DAOAhorro::DAOAhorro()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAOAhorro::~DAOAhorro()
{
    connection->disConnect();
    delete connection;
}

void DAOAhorro::CrearAhorro(QString params[3]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO ahorro( ahorro_valor, ahorro_fecha, fondo_id, usuario_cedula) VALUES ( ?, ?, 1, ?)") ))
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
            query->addBindValue(params[2]);
        }

        bool result = connection->executeInsert(query);
        if( result )
            qDebug() << "Successful insert";
        else
            qDebug() << "Insert failed";

        delete query;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
}

QList<QList<QString>> DAOAhorro::ConsultarAhorro(QString fechaInicio, QString fechaFin){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from ahorro where ahorro_fecha between ? and ? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(fechaInicio);
            query->addBindValue(fechaFin);
        }


        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        while(query->next()){
            QList<QString> answer;
            answer << query->value(0).toString();
            answer << query->value(1).toString();
            answer << query->value(2).toString();
            answer << query->value(3).toString();
            answer << query->value(4).toString();
            answers << answer;
        }

        delete query;
        return answers;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answers;
}

QList<QList<QString>> DAOAhorro::ConsultarAhorro(QString cedula){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from ahorro where usuario_cedula =? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
            query->addBindValue(cedula);

        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        while(query->next()){
            QList<QString> answer;
            answer << query->value(0).toString();
            answer << query->value(1).toString();
            answer << query->value(2).toString();
            answer << query->value(3).toString();
            answer << query->value(4).toString();
            answers << answer;
        }

        delete query;
        return answers;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answers;
}
