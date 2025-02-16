#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QSqlDatabase>

class DataBase
{
public:
    DataBase();
    ~DataBase();
    void createConnection();
private:
    QSqlDatabase* db;
    QString* db_input;
    QSqlQuery* query;
};

#endif // DATABASE_H
