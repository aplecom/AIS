#include "database.h"

DataBase::DataBase()
{}

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
      qDebug()<<"БД работает корректно!";
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

void DataBase::addPatient(const QString& name, const QString& last_name, const QDate& date, const QString& phone)
{
    QString str = "INSERT INTO public.Patient (name, last_name, date_birth, phone)"
                  " VALUES (:name, :last_name, :date, :phone);";
    db_input = str;
    query.prepare(db_input);
    query.bindValue(":name",name);
    query.bindValue(":last_name",last_name);
    query.bindValue(":date",date.toString("yyyy-MM-dd"));
    query.bindValue(":phone",phone);

    if(!query.exec())
        qDebug()<<"Не удалось добавить данные в БД"<<query.lastError().text();
    else
        qDebug()<<"Успешно! Данные добавились в БД";
}

bool DataBase::addAppointment(int& doctorId, int& patientId, const QDateTime& dateTime)
{
    QString str = "INSERT INTO public.appointments (doctor_id, patient_id, appointment_date) "
                  "VALUES (:doctorId, :patientId, :dateTime);";

    query.prepare(str);
    query.bindValue(":doctorId", doctorId);
    query.bindValue(":patientId", patientId);
    query.bindValue(":dateTime", dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec())
        qDebug() << "Ошибка добавления приёма: " << query.lastError().text();
    else
    {
        qDebug() << "Приём успешно добавлен!";
        return true;
    }
    return false;
}

QVector<QVector<QString>> DataBase::getAppointmentsList(int doctor_id)
{
    QVector<QVector<QString>> appointmentsData;

    QString str_t = "SELECT a.id, p.name AS patient_name, p.last_name AS patient_last_name, "
                    "a.appointment_date "
                    "FROM public.appointments a "
                    "JOIN public.patient p ON a.patient_id = p.id "
                    "WHERE a.doctor_id = :doctor_id "
                    "ORDER BY a.appointment_date;";

    query.prepare(str_t);
    query.bindValue(":doctor_id", doctor_id);

    if (!query.exec())
    {
        qDebug() << "Ошибка загрузки записей: " << query.lastError().text();
        return {};
    }

    while (query.next())
    {
        QString appointmentId = query.value(0).toString();
        QString patientName = query.value(1).toString();
        QString patientLastName = query.value(2).toString();
        QString appointmentDateTime = query.value(3).toString();

        QStringList dateTimeParts = appointmentDateTime.split("T");
        QString appointmentDate = dateTimeParts.value(0);
        QString appointmentTime = dateTimeParts.value(1).left(5);

        appointmentsData.append({appointmentId, patientName + " " + patientLastName, appointmentDate, appointmentTime});
    }

    return appointmentsData;
}


void DataBase::removeAppointment(const QString& appointmentId)
{
    query.prepare("DELETE FROM public.appointments WHERE id = :id");
    query.bindValue(":id", appointmentId);

    if (!query.exec())
        qDebug() << "Ошибка удаления приёма: " << query.lastError().text();
    else
    {
        qDebug() << "Приём успешно удалён!";
    }
}

DataBase::~DataBase(){}
