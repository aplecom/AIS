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

QString DataBase::autoUser(QString& newLogin, QString& newPassword)
{
    QSqlRecord rec;
    QString str_t = "SELECT login, password, (SELECT name FROM public.positions WHERE id = s.positions_id) AS position "
                    "FROM public.staff s "
                    "WHERE login = '%1'";
    QString login,password,position;

    db_input = str_t.arg(newLogin);
    if (!execQuery(query,db_input))
        return "Ошибка";

    query.next();
    rec = query.record();

    login = query.value(rec.indexOf("login")).toString();
    password = query.value(rec.indexOf("password")).toString();
    position = query.value(rec.indexOf("position")).toString();

    if(newLogin!=login || newPassword!=password ||
            login=="" || password=="")
    {
        qDebug()<<"Ошибка входа по данным:"
                  "логин: "<<newLogin<<
                  "пароль: "<<newPassword;
        return "Ошибка";
    }
    else
    {
        qDebug()<<"Удалось войти в учетную запись, как" <<position<<": "
                  "логин: "<<login<<
                  "пароль: "<<password;
        return position;
    }

}
bool DataBase::execQuery(QSqlQuery& query, QString& db_input)
{
    if(!query.exec(db_input))
    {
        qDebug()<<"Ошибка запроса: "<<query.lastError().text();
        return false;
    }
    else
        return true;
}

DataBase::~DataBase(){}
