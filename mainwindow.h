#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "database.h"
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <qDebug>



class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mWindDesign();

private slots:
    void on_btnLogIn_button_clicked();

private:
    const int WIDTH = 800;
    const int HEIGHT = 600;

    QVBoxLayout* layout;
    QLabel *lbHeader, *lbLogo;
    QLineEdit *lnEdLogin, *lnEdPassword;
    QPushButton *btnLogIn;
    QHBoxLayout* layoutHeader;

    DataBase db;

    QString newLogin, newPassword;

};

#endif // MAINWINDOW_H
