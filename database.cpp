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

QStringList DataBase::getDoctorsList()
{

    QSqlRecord rec;
    QString str_t = "SELECT id, name, last_name, specialization FROM public.doctors ORDER BY id";

    db_input = str_t;

    if(!execQuery(query,db_input))
        return QStringList("Не удалось загрузить данные");

    QStringList doctorsList;

    while(query.next())
    {
        rec = query.record();
        QString doctorName = query.value(rec.indexOf("name")).toString();
        QString doctorLastName = query.value(rec.indexOf("last_name")).toString();
        QString doctorSpecialization = query.value(rec.indexOf("specialization")).toString();
        QString id = query.value(rec.indexOf("id")).toString();

        QString doctorInfo = id + " : " + doctorName + " " + doctorLastName + " - " + doctorSpecialization;
        doctorsList.append(doctorInfo);
    }

    return doctorsList;
}

QStringList DataBase::getPatientList()
{
    QSqlRecord rec;
    QString str_t = "SELECT id, name, last_name FROM public.Patient ORDER BY id";

    db_input = str_t;

    if(!execQuery(query,db_input))
        return QStringList("Не удалось загрузить данные");

    QStringList patientList;

    while(query.next())
    {
        rec = query.record();
        QString name = query.value(rec.indexOf("name")).toString();
        QString last_name =   query.value(rec.indexOf("last_name")).toString();
        QString id =  query.value(rec.indexOf("id")).toString();

        QString patientInfo = id + " : " + name + " " + last_name;
        patientList.append(patientInfo);
    }
    return patientList;
}

void DataBase::removePatient(const QString& ID)
{
    query.prepare("DELETE FROM public.Patient WHERE id = :ID");
    query.bindValue(":ID", ID);

    if (!query.exec())
    {
        qDebug() << "Ошибка удаления пациента " << query.lastError().text();
    }

    QString resetSeqQuery = "SELECT setval('Patient_id_seq', (SELECT max(id) FROM public.Patient))";
    if (!execQuery(query, resetSeqQuery))
    {
        qDebug() << "Ошибка при сбросе последовательности: " << query.lastError().text();
    }
}


DataBase::~DataBase(){}
