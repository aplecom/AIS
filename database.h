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
    QString autoUser(QString& newLogin, QString& newPassword);
    bool execQuery(QSqlQuery& query, QString& db_input);
    QStringList getDoctorsList();
    QStringList getPatientList();
    void removePatient(const QString& ID);
    void addPatient(const QString& name, const QString& last_name, const QDate& date, const QString& phone);
    bool addAppointment(int& doctorId, int& patientId, const QDateTime& dateTime);
    QVector<QVector<QString>> getAppointmentsList(int doctor_id);
    bool removeAppointment(const QString& appointmentId);
private:
    QSqlDatabase db;
    QString db_input;
    QSqlQuery query;
};

#endif // DATABASE_H
