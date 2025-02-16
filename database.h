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
    bool autoUser(QString& newLogin, QString& newPassword);
    bool execQuery(QSqlQuery& query, QString& db_input);
private:
    QSqlDatabase db;
    QString db_input;
    QSqlQuery query;
};

#endif // DATABASE_H
