#include "database.h"

DataBase::DataBase()
{

}

void DataBase::createConnection()
{
    db =QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Hospital");
    db.setUserName("admin");
    db.setPassword("admin");
    db.setHostName("localhost");
    if(!db.open())
    {
      qDebug()<<"Не удалось подключиться к БД";
      qDebug()<<db.lastError().text();
    }
    else
    {
      query = QSqlQuery(db);
      qDebug()<<"Красавчик! БД в твоей власти!";
    }
}

bool DataBase::autoUser(QString& newLogin, QString& newPassword)
{
    QSqlRecord rec;
    QString str_t = "SELECT * FROM Admins WHERE login = '%1'";
    QString login,password;

    db_input = str_t.arg(newLogin);
    if (execQuery(query,db_input))
        return false;

    query.next();
    rec = query.record();

    login = query.value(rec.indexOf("login")).toString();
    password = query.value(rec.indexOf("password")).toString();

    if(newLogin==login && newPassword==password)
    {
        qDebug()<<"Удалось войти в учетную запись:"
                  "логин: "<<login<<
                  "пароль: "<<password;
        return true;
    }
    else
    {
        qDebug()<<"Ошибка входа по данным:"
                  "логин: "<<login<<
                   "пароль: "<<password;
        return false;
    }

}
bool DataBase::execQuery(QSqlQuery& query, QString& db_input)
{
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса: "<<query.lastError().text();
        return false;
    }
}

DataBase::~DataBase()
{

}
