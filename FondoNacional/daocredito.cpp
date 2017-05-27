#include "daocredito.h"

DAOCredito::DAOCredito()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAOCredito::~DAOCredito()
{
    connection->disConnect();
    delete connection;
}

void DAOCredito::CrearCredito(QString params[12]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO credito( credito_ingreso_familiar, credito_nombre_empresa, credito_telefono_empresa, credito_tiempo_laborando, "
                "credito_valor_prestamo, credito_total_gastos, credito_plazo_credito, credito_numero_meses,"
                " credito_valor_aprobacion, credito_fecha, credito_estado, fondo_id, usuario_cedula) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 1, ?)") ))
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
            query->addBindValue(params[2]);
            query->addBindValue(params[3]);
            query->addBindValue(params[4]);
            query->addBindValue(params[5]);
            query->addBindValue(params[6]);
            query->addBindValue(params[7]);
            query->addBindValue(params[8]);
            query->addBindValue(params[9]);
            query->addBindValue(params[10]);
            query->addBindValue(params[11]);
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

void DAOCredito::ActualizarEstado(QString referencia, QString estado){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE credito set credito_estado=? where credito_referencia=? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(estado);
            query->addBindValue(referencia);
        }

        bool result = connection->executeUpdate(query);
        if( result )
            qDebug() << "Successful update";
        else
            qDebug() << "Update failed";

        delete query;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
}

QList<QList<QString>> DAOCredito::ConsultarCredito(QString fechaInicio, QString fechaFin, QString estado){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from credito where credito_estado=? and credito_fecha between ? and ? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(estado);
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
            answer << query->value(5).toString();
            answer << query->value(6).toString();
            answer << query->value(7).toString();
            answer << query->value(8).toString();
            answer << query->value(9).toString();
            answer << query->value(10).toString();
            answer << query->value(11).toString();
            answer << query->value(12).toString();
            answer << query->value(13).toString();
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

QList<QList<QString>> DAOCredito::ConsultarCredito(QString cedula){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from credito where usuario_cedula =? ")) )
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
            answer << query->value(5).toString();
            answer << query->value(6).toString();
            answer << query->value(7).toString();
            answer << query->value(8).toString();
            answer << query->value(9).toString();
            answer << query->value(10).toString();
            answer << query->value(11).toString();
            answer << query->value(12).toString();
            answer << query->value(13).toString();
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
