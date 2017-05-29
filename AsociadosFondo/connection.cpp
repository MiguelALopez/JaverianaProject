#include "connection.h"

Connection::Connection(const char* driver)
{
    db = new QSqlDatabase( QSqlDatabase::addDatabase(driver) );
}

Connection::~Connection()
{
    qDebug() << "Called Destructor!";
    delete db;
}

QSqlDatabase* Connection::connect()
{
    QString server = "localhost";
    QString databaseName = "fondo";
    QString userName = "miguel";
    QString password = "123456";
    db->setConnectOptions();
    db->setHostName(server);
    db->setDatabaseName(databaseName);
    db->setUserName(userName);
    db->setPassword(password);

    if(db->open()) {
        return db;
    }
    else {
        return NULL;
    }
}

int Connection::selectRowCountResult(QSqlQuery* query)
{
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        return -1;
    }

    int recordCount = 0;
    while (query->next())
    {
        qDebug() << "Field 1 : " << query->value(0).toString()
                 << "Field 2 : " << query->value(1).toString();
        ++recordCount;
    }

    return recordCount;
}

bool Connection::executeSelect(QSqlQuery* query)
{
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        return false;
    }
    return true;
}

bool Connection::executeInsert(QSqlQuery* query)
{
    db->transaction();
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        db->rollback();
        return false;
    }
    db->commit();
    return true;
}

bool Connection::executeUpdate(QSqlQuery* query)
{
    db->transaction();
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        db->rollback();
        return false;
    }
    db->commit();
    return true;
}

bool Connection::executeDelete(QSqlQuery* query)
{
    db->transaction();
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        db->rollback();
        return false;
    }
    db->commit();
    return true;
}

void Connection::disConnect()
{
    qDebug() << "Disconnected From Database!";
    db->close();
}
