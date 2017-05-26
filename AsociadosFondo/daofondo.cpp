#include "daofondo.h"

DAOFondo::DAOFondo()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAOFondo::~DAOFondo()
{
    connection->disConnect();
    delete connection;
}

void DAOFondo::ActualizarFondo(QString params[2]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE fondo set fondo_smmlv=?, fondo_iva=? where fondo_id =1 ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
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

QList<QString> DAOFondo::ConsultarFondo(){
    QList<QString> answer;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT fondo_id, fondo_smmlv, fondo_iva from fondo where fondo_id = 1 ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }

        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        query->next();
        answer << query->value(0).toString();
        answer << query->value(1).toString();
        answer << query->value(2).toString();

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}

void DAOFondo::ActualizarPropiedadesAhorro(QString params[2]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE propiedades_ahorro set propiedades_ahorro_tasamax=?, propiedades_ahorro_tasamin=? where fondo_id =1 and propiedades_ahorro_id = ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
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

QList<QString> DAOFondo::ConsultarPropiedadesAhorro(){
    QList<QString> answer;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT propiedades_ahorro_id, propiedades_ahorro_tasamax, propiedades_ahorro_tasamin, fondo_id from propiedades_ahorro where propiedades_ahorro_id = 1 ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }

        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        query->next();
        answer << query->value(0).toString();
        answer << query->value(1).toString();
        answer << query->value(2).toString();
        answer << query->value(3).toString();

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}

void DAOFondo::ActualizarPropiedadesCredito(QString params[7]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE propiedades_credito set propiedades_credito_tasa=?, propiedades_credito_montomax=?, propiedades_credito_tiempomax=?,"
                                    "propiedades_credito_antiguedad=?, propiedades_credito_administracion=?, propiedades_credito_seguro=?,"
                                    "propiedades_credito_valor_plataforma=? where propiedades_credito_id=1 ")) )
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

QList<QString> DAOFondo::ConsultarPropiedadesCredito(){
    QList<QString> answer;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT propiedades_credito_id, propiedades_credito_tasa, propiedades_credito_montomax, propiedades_credito_tiempomax,"
                                    "propiedades_credito_antiguedad, propiedades_credito_administracion, propiedades_credito_seguro,"
                                    "propiedades_credito_valor_plataforma, fondo_id from propiedades_credito where propiedades_credito_id = 1 ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }

        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        query->next();
        answer << query->value(0).toString();
        answer << query->value(1).toString();
        answer << query->value(2).toString();

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}

void DAOFondo::ActualizarPropiedadesAuxilio(QString params[4]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE propiedades_auxilio set propiedades_auxilio_tasa_calamidad=?, propiedades_auxilio_tasa_educacion=?,"
                                    "propiedades_auxilio_aux_max_calamidad=?, propiedades_auxilio_valor_max_aux=? where propiedades_auxilio_id =1 ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(params[0]);
            query->addBindValue(params[1]);
            query->addBindValue(params[2]);
            query->addBindValue(params[4]);
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

QList<QString> DAOFondo::ConsultarPropiedadesAuxilio(){
    QList<QString> answer;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT propiedades_auxilio_id, propiedades_auxilio_tasa_calamidad, propiedades_auxilio_tasa_educacion,"
                                    "propiedades_auxilio_aux_max_calamidad, propiedades_auxilio_valor_max_aux from propiedades_auxilio where fondo_id = ? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }

        bool result = connection->executeSelect(query);
        if( result )
            qDebug() << "Successful select";
        else
            qDebug() << "Select failed";

        query->next();
        answer << query->value(0).toString();
        answer << query->value(1).toString();
        answer << query->value(2).toString();

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}
