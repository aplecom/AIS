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
    QPushButton* btnAddPatient1;
    QPushButton* btnRemovePatient;
    QPushButton* btnAddPatient2;
    QPushButton* btnBackPatInList;

    QGridLayout* gLayout;
    QVBoxLayout* doctorsMenuLayout;
    QVBoxLayout* patienstMenuLayout;
    QVBoxLayout* mainMenuLayout;
    QVBoxLayout* patientsAddLayout;

    QStackedWidget* infoStack;
    QStackedWidget* menuStack;

    QListWidget* lWDoctors;
    QListWidget* lwPatient;

    QWidget* mainMenu;
    QWidget* doctorMenu;
    QWidget* patientMenu;
    QWidget* patientAddMenu;
    QWidget* infoAddPatient;

    QLineEdit* lEditName;
    QLineEdit* lEditLastName;
    QLineEdit* lEditDate;
    QLineEdit* lEditPhone;

    QLabel* lbLogo;
    QLabel* lbName;
    QLabel* lbLastName;
    QLabel* lbDate;
    QLabel* lbPhone;

    QHBoxLayout* nameLt;
    QHBoxLayout* lastNameLt;
    QHBoxLayout* dateLt;
    QHBoxLayout* phoneLt;

    QVBoxLayout* addPatLt;

    void design_infoAddPatient();



};

#endif // ADMIN_H
