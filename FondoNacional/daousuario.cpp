#include "daousuario.h"

DAOUsuario::DAOUsuario()
{
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    connection = new Connection(driverName);
    db = connection->connect();
}

DAOUsuario::~DAOUsuario()
{
    connection->disConnect();
    delete connection;
}

void DAOUsuario::CrearUsuario(QString params[11]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // insert into empty usuarios table
        if( !query->prepare(
        QString("INSERT INTO usuario( usuario_cedula, usuario_password, usuario_nombre, usuario_apellido, usuario_fechaNacimiento, usuario_telefono, usuario_direccion, usuario_sexo, usuario_estado_civil, usuario_correo, usuario_ingresos) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)") ))
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

void DAOUsuario::ActualizarUsuario(QString params[11]){
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Update usuarios
        if( !query->prepare(QString("UPDATE usuario set usuario_password=?, usuario_nombre=?, usuario_apellido=?, usuario_fechaNacimiento=?,"
                                    "usuario_telefono=?, usuario_direccion=?, usuario_sexo=?, usuario_estado_civil=?, usuario_correo=?,"
                                    " usuario_ingresos=? where usuario_cedula =? ")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
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
            query->addBindValue(params[0]);
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

QList<QString> DAOUsuario::ConsultarUsuario(QString cedula){
    QList<QString> answer;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT usuario_cedula, usuario_password, usuario_nombre, usuario_apellido, usuario_fechaNacimiento, usuario_telefono, usuario_direccion, "
                                    "usuario_sexo, usuario_estado_civil, usuario_correo, usuario_ingresos from usuario where usuario_cedula = ? ")) )
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

        query->next();
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

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}

bool DAOUsuario::ConsultarLogin(QString cedula, QString password){
    bool answer = false;
    if(db->open()) {

        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        // Select empty usuario table
        if( !query->prepare(QString("SELECT usuario_cedula, usuario_password from usuario where usuario_cedula = ? and usuario_password = ?")) )
        {
            qDebug() <<"Error = " << db->lastError().text();
        }
        else
        {
            query->addBindValue(cedula);
            query->addBindValue(password);
        }

        int queryResultRowCount = connection->selectRowCountResult(query);
        if (queryResultRowCount>=1){
            answer = true;
        }

        delete query;
        return answer;
    }
    else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }
    return answer;
}
