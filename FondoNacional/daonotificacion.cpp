#include "daonotificacion.h"

DAONotificacion::DAONotificacion()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAONotificacion::~DAONotificacion()
{
    connection->disConnect();
    delete connection;
}

void DAONotificacion::CrearNotificacion(QString params[4]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO notificacion( notificacion_titulo, notificacion_descripcion, notificacion_fecha, usuario_cedula) VALUES ( ?, ?, ?, ?)") ))
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
            query->addBindValue(params[2]);
            query->addBindValue(params[3]);
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

QList<QList<QString>> DAONotificacion::ConsultarNotificacion(QString cedula){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from notificacion where usuario_cedula =? ")) )
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
