#ifndef CONNECTION_H
#define CONNECTION_H


#include <QtSql>
#include <QString>
#include <QDebug>

class Connection
{
public:
    Connection(const char* driver);
    ~Connection();
    QSqlDatabase* connect();
    void disConnect();

    int selectRowCountResult(QSqlQuery* query);
    bool executeInsert(QSqlQuery* query);
    bool executeUpdate(QSqlQuery* query);
    bool executeDelete(QSqlQuery* query);
    bool executeSelect(QSqlQuery* query);

private:
    QSqlDatabase* db;
};

#endif // CONNECTION_H
