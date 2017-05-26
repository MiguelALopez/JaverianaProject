#include "daofaq.h"

DAOFaq::DAOFaq()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect("localhost", "prueba", "postgres", "juand");
}

DAOFaq::~DAOFaq()
{
    connection->disConnect();
    delete connection;
}

void DAOFaq::CrearFaq(QString params[3]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO faq( faq_titulo, faq_estado, fondo_id, usuario_cedula) VALUES ( ?, ?, 1, ?)") ))
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

void DAOFaq::ActualizarFaq(QString referencia, QString descripcion, QString estado){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE faq set faq_descripcion=?, faq_estado=? where faq_referencia=? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(descripcion);
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

QList<QList<QString>> DAOFaq::ConsultarFaq(QString estado){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from faq where faq_estado =?")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(estado);
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

QList<QList<QString>> DAOFaq::ConsultarFaq(){
    QList<QList<QString>> answers;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT * from faq")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
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
