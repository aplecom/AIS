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

    QGridLayout* gLayout;
    QVBoxLayout* doctorsMenuLayout;
    QVBoxLayout* patienstMenuLayout;
    QVBoxLayout* mainMenuLayout;
    QVBoxLayout* patientsAddLayout;
    QVBoxLayout* meetMenuLayotC;
    QVBoxLayout* lookMeetingsMenuLayout;

    QStackedWidget* infoStack;
    QStackedWidget* menuStack;

    QListWidget* lWDoctors;
    QListWidget* lwPatient;

    QWidget* mainMenu;
    QWidget* doctorMenu;
    QWidget* patientMenu;
    QWidget* patientAddMenu;
    QWidget* infoAddPatient;
    QWidget* addMeetMenu;
    QWidget* lookMeetingsMenu;

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

    void design_infoAddPatient();
    void clearInfoLb();
    void clearDatePatLb();

};

#endif // ADMIN_H
