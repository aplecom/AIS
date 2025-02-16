#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <qDebug>
#include <QtSql>
#include <QSqlDatabase>



class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    const int WIDTH = 800;
    const int HEIGHT = 600;

    QVBoxLayout* layout;
    QLabel *lbHeader, *lbLogo;
    QLineEdit *lnEdLogin, *lnEdPassword;
    QPushButton *btnLogIn;
    QHBoxLayout* layoutHeader;

    QSqlDatabase db;
    QString db_input;
    QSqlQuery query;
};

#endif // MAINWINDOW_H
