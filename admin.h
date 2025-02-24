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
    void on_btnAddPatient(); // не в разработке
    void on_btnRemovePatient();


private:
    const int WIDTH = 1200;
    const int HEIGHT = 800;

    QWidget* mainWindow;
    DataBase &db;

    QPushButton* btnDoctors;
    QPushButton* btnPatients;
    QPushButton* btnExit;
    QPushButton* btnBack1;
    QPushButton* btnBack2;
    QPushButton* btnAddPatient;
    QPushButton* btnRemovePatient;

    QGridLayout* gLayout;
    QVBoxLayout* doctorsMenuLayout;
    QVBoxLayout* patienstMenuMenuLayout;
    QVBoxLayout* mainMenuLayout;

    QLabel* lbLogo;

    QStackedWidget* stackWidget;
    QStackedWidget* menuStack;

    QListWidget* lWDoctors;
    QListWidget* lwPatient;

    QWidget* mainMenu;
    QWidget* doctorMenu;
    QWidget* patientMenu;


};

#endif // ADMIN_H
