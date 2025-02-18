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

    gLayout = new QGridLayout(this);
    vLayout = new QVBoxLayout();

    btnDoctors = new QPushButton("Доктора",this);
    btnPatients =  new QPushButton("Пациенты",this);
    btnMeetings= new QPushButton("Приемы",this);
    btnExit =new QPushButton("Выйти",this);

    lbLogo = new QLabel(this);

    stackWidget = new QStackedWidget(this);

    lbLogo->setPixmap(logo);
    lbLogo->setFixedSize(80,80);

    vLayout->addWidget(lbLogo);
    vLayout->addWidget(btnDoctors);
    vLayout->addWidget(btnPatients);
    vLayout->addWidget(btnMeetings);
    vLayout->addWidget(btnExit);

    gLayout->addLayout(vLayout,0,0,4,1);
    gLayout->addWidget(stackWidget,0,1,4,3);

    QStringList listDoctoes = db.getDoctorsList();
    lWDoctors = new QListWidget();

    lWDoctors->addItems(listDoctoes);

    stackWidget->addWidget(lWDoctors);

}

Admin::~Admin() {}
