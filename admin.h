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

private:
    const int WIDTH = 1200;
    const int HEIGHT = 800;

    QWidget* mainWindow;
    DataBase &db;
    QPushButton *btnDoctors, *btnPatients, *btnExit;
    QGridLayout* gLayout;
    QVBoxLayout* vLayout;
    QLabel* lbLogo;
    QStackedWidget* stackWidget;
    QListWidget* lWDoctors;
    QListWidget* lwPatient;

};

#endif // ADMIN_H
