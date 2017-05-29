#include "daoauxilio.h"

DAOAuxilio::DAOAuxilio()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAOAuxilio::~DAOAuxilio()
{
    connection->disConnect();
    delete connection;
}

void DAOAuxilio::CrearAuxilio(QString params[6]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO auxilio( auxilio_tipo, auxilio_valor, auxilio_valor_aprobacion, auxilio_fecha, "
                "auxilio_estado, fondo_id, usuario_cedula) VALUES ( ?, ?, ?, ?, ?, 1, ?)") ))
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

void DAOAuxilio::ActualizarEstado(QString referencia, QString estado, QString monto){
    QString fechaActual = QDate::currentDate().toString("yyyy-MM-dd");
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE auxilio set auxilio_estado=?, auxilio_fecha=?, auxilio_valor_aprobacion=? where auxilio_referencia=? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(estado);
            query->addBindValue(fechaActual);
            query->addBindValue(monto);
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

QList<QList<QString>> DAOAuxilio::ConsultarAuxilio(QString fechaInicio, QString fechaFin, QString estado){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from auxilio where auxilio_estado=? and auxilio_fecha between ? and ? ")) )
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
            answer << query->value(1).toString();
            answer << QString::number(query->value(2).toInt(), 'g', 15);
            answer << QString::number(query->value(3).toInt(), 'g', 15);
            answer << query->value(4).toString();
            answer << query->value(5).toString();
            answer << QString::number(query->value(6).toInt(), 'g', 15);
            answer << QString::number(query->value(7).toInt(), 'g', 15);

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

double DAOAuxilio::CuentaAuxilios(){
    double answer = 0;
    QString annoActual = QDate::currentDate().toString("yyyy");
    QString fechaInicio = annoActual + "-01-01";
    QString fechaFin = annoActual + "-12-31";
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT sum(auxilio_valor_aprobacion) FROM auxilio WHERE auxilio_estado = 'Aprobado' and auxilio_fecha BETWEEN ? and ?")) )
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
            answer = query->value(0).toDouble();
            qDebug() << query->value(0);
        }

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}

QList<QList<QString>> DAOAuxilio::ConsultarAuxilio(QString cedula){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from auxilio where usuario_cedula =? ")) )
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
