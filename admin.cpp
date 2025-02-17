#include "admin.h"

Admin::Admin(DataBase &database, QWidget* parent)
    :QWidget(parent), db(database)
{
    admDesign();
}

void Admin::admDesign()
{
    setMinimumSize(WIDTH,HEIGHT);
    setWindowTitle("Администратор");

    QPixmap background(":/img/img/background.jpg");
    QPixmap logo(":/img/img/logo.png");
    logo = logo.scaled(80, 80, Qt::KeepAspectRatio);

    QPalette  palette;
    palette.setBrush(QPalette::Background, QBrush(background));
    setPalette(palette);
}

Admin::~Admin() {}
