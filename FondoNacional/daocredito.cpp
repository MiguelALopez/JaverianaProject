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

void DAOCredito::ActualizarEstado(QString referencia, QString estado, QString valor){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE credito set credito_estado=?, credito_valor_aprobacion=? where credito_referencia=? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(estado);
            query->addBindValue(valor);
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
            answer << QString::number(query->value(0).toInt(), 'g', 15);
            answer << QString::number(query->value(1).toInt(), 'g', 15);
            answer << query->value(2).toString();
            answer << QString::number(query->value(3).toInt(), 'g', 15);
            answer << QString::number(query->value(4).toInt(), 'g', 15);
            answer << QString::number(query->value(5).toInt(), 'g', 15);
            answer << QString::number(query->value(6).toInt(), 'g', 15);
            answer << QString::number(query->value(7).toInt(), 'g', 15);
            answer << QString::number(query->value(8).toInt(), 'g', 15);
            answer << QString::number(query->value(9).toInt(), 'g', 15);
            answer << query->value(10).toString();
            answer << query->value(11).toString();
            answer << QString::number(query->value(12).toInt(), 'g', 15);
            answer << QString::number(query->value(13).toInt(), 'g', 15);
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
            answer << QString::number(query->value(0).toInt(), 'g', 15);
            answer << QString::number(query->value(1).toInt(), 'g', 15);
            answer << query->value(2).toString();
            answer << QString::number(query->value(3).toInt(), 'g', 15);
            answer << QString::number(query->value(4).toInt(), 'g', 15);
            answer << QString::number(query->value(5).toInt(), 'g', 15);
            answer << QString::number(query->value(6).toInt(), 'g', 15);
            answer << QString::number(query->value(7).toInt(), 'g', 15);
            answer << QString::number(query->value(8).toInt(), 'g', 15);
            answer << QString::number(query->value(9).toInt(), 'g', 15);
            answer << query->value(10).toString();
            answer << query->value(11).toString();
            answer << QString::number(query->value(12).toInt(), 'g', 15);
            answer << QString::number(query->value(13).toInt(), 'g', 15);
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
