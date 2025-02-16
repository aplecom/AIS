#include "database.h"

DataBase::DataBase()
{

}


void DataBase::createConnection()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db->setDatabaseName("Hospital");
    db->setUserName("admin");
    db->setPassword("admin");
    db->setHostName("localhost");
    if(!db->open())
    {
      qDebug()<<"Не удалось подключиться к БД";
      qDebug()<<db->lastError().text();
    }
    else
    {
      query = new QSqlQuery(*db);
      qDebug()<<"Красавчик! БД в твоей власти!";
    }

}

DataBase::~DataBase()
{

}
