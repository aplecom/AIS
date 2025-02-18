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
    Admin(DataBase &database, QWidget* parent = nullptr);
    ~Admin();

    void admDesign();

private:
    const int WIDTH = 1200;
    const int HEIGHT = 800;

    DataBase &db;
    QPushButton *btnDoctors, *btnPatients, *btnMeetings, *btnExit;
    QGridLayout* gLayout;
    QVBoxLayout* vLayout;
    QLabel* lbLogo;
    QStackedWidget* stackWidget;
    QListWidget* lWDoctors;

};

#endif // ADMIN_H
