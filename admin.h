#ifndef ADMIN_H
#define ADMIN_H

#include "database.h"
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QDateTimeEdit>

class Admin: public QWidget
{
    Q_OBJECT
public:
    Admin(DataBase &database, QWidget* mainWindow, QWidget* parent = nullptr);
    ~Admin();

    void admDesign();
private slots:
    void on_btnDoctors_clicked();
    void on_btnPatients_clicked();
    void on_btnExit_clicked();
    void showMainMenu();
    void on_btnAddPatient1();
    void on_btnRemovePatient();
    void on_btnAddPatient2();
    void on_btnBackPatInList();
    void on_btnAddMeet();
    void on_btnBackDocInList();
    void on_btnLookMeetings();
    void on_btnSelectPatient();
    void onCalendarDateSelected();
    void on_btnBackCalendar();
    void on_btnSelectPatient2();

private:
    const int WIDTH = 1200;
    const int HEIGHT = 800;

    QWidget* mainWindow;
    DataBase &db;

    QPushButton* btnDoctors;
    QPushButton* btnPatients;
    QPushButton* btnExit;
    QPushButton* btnBackDocInMenu;
    QPushButton* btnBackPacInMenu;
    QPushButton* btnAddMeet;
    QPushButton* btnLookMeetings;
    QPushButton* btnAddPatient1;
    QPushButton* btnRemovePatient;
    QPushButton* btnAddPatient2;
    QPushButton* btnBackPatInList;
    QPushButton* btnBackDocInList;
    QPushButton* btnBackDocInListForLook;
    QPushButton* btnSelectPatient1;
    QPushButton* btnSelectPatient2;
    QPushButton* btnBackCalendar;


    QGridLayout* gLayout;
    QVBoxLayout* doctorsMenuLayout;
    QVBoxLayout* patienstMenuLayout;
    QVBoxLayout* mainMenuLayout;
    QVBoxLayout* patientsAddLayout;
    QVBoxLayout* meetMenuLayoutC;
    QVBoxLayout* lookMeetingsMenuLayout;
    QVBoxLayout* selectPatientLayout;

    QStackedWidget* infoStack;
    QStackedWidget* menuStack;

    QListWidget* lWDoctors;
    QListWidget* lwPatient;
    QListWidget* lWAppointments;

    QWidget* mainMenu;
    QWidget* doctorMenu;
    QWidget* patientMenu;
    QWidget* patientAddMenu;
    QWidget* infoAddPatient;
    QWidget* addMeetMenu;
    QWidget* lookMeetingsMenu;
    QWidget* selectPatientMenu;

    QLineEdit* lEditName;
    QLineEdit* lEditLastName;
    QDateEdit* lEditDate;
    QLineEdit* lEditPhone;

    QLabel* lbLogo;
    QLabel* lbName;
    QLabel* lbLastName;
    QLabel* lbDate;
    QLabel* lbPhone;

    QLabel* infoName;
    QLabel* infoLastName;
    QLabel* infoDate;
    QLabel* infoPhone;

    QLabel* sucAddPat;

    QHBoxLayout* nameLt;
    QHBoxLayout* lastNameLt;
    QHBoxLayout* dateLt;
    QHBoxLayout* phoneLt;

    QVBoxLayout* addPatLt;

    QCalendarWidget* calendar;

    QDateTimeEdit* dateTimeEdit;

    QWidget* calendarAndDateWidget;

    QVBoxLayout* calendarLayout;

    void design_infoAddPatient();
    void clearInfoLb();
    void clearDatePatLb();

    int doctorID, patientID;
    QDateTime dateTime;

};

#endif // ADMIN_H
