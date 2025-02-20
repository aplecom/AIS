#include "admin.h"

Admin::Admin(DataBase &database, QWidget* mainWindow, QWidget* parent)
    : QWidget(parent), db(database), mainWindow(mainWindow)
{
    admDesign();
    connect(btnDoctors,&QPushButton::clicked,this,&Admin::on_btnDoctors_clicked);
    connect(btnPatients, &QPushButton::clicked, this, &Admin::on_btnPatients_clicked);
    connect(btnExit,&QPushButton::clicked, this, &Admin::on_btnExit_clicked);
}

void Admin::admDesign()
{
    setMinimumSize(WIDTH,HEIGHT);
    setWindowTitle("Администратор");

    QPixmap background(":/img/img/background.jpg");
    QPixmap logo(":/img/img/logo.png");
    logo = logo.scaled(200, 200, Qt::KeepAspectRatio);

    QPalette  palette;
    palette.setBrush(QPalette::Background, QBrush(background));
    setPalette(palette);

    gLayout = new QGridLayout(this);
    vLayout = new QVBoxLayout();

    btnDoctors = new QPushButton("Доктора",this);
    btnPatients =  new QPushButton("Пациенты",this);
    btnExit =new QPushButton("Выйти",this);

    lbLogo = new QLabel(this);

    stackWidget = new QStackedWidget(this);

    lbLogo->setPixmap(logo);
    lbLogo->setFixedSize(230,230);

    vLayout->addWidget(lbLogo);
    vLayout->addWidget(btnDoctors);
    vLayout->addWidget(btnPatients);
    vLayout->addWidget(btnExit);

    gLayout->addLayout(vLayout,0,0,4,1);
    gLayout->addWidget(stackWidget,0,1,4,3);

    lWDoctors = new QListWidget();
    stackWidget->addWidget(lWDoctors);
    lwPatient = new QListWidget();
    stackWidget->addWidget(lwPatient);

    lbLogo->setStyleSheet("margin-left: 30px; ");
    stackWidget->setStyleSheet("font-size: 20px; ");

    this->setStyleSheet(
    "QPushButton {"
    " font-size: 20px;"
    " border-radius: 10px;"
    " border: 2px solid black;"
    " padding: 10px;"
    " background-color: white;"
    "}"
    " QPushButton:hover {"
    " background-color: rgb(3, 198, 252);"
    " }"
    " QPushButton:pressed {"
    " background-color: rgb(3, 240, 252);"
    "}");
}

void Admin::on_btnDoctors_clicked()
{
    QStringList listDoctors = db.getDoctorsList();
    lWDoctors->clear();
    lWDoctors->addItems(listDoctors);
    stackWidget->setCurrentWidget(lWDoctors);
}

void Admin::on_btnPatients_clicked()
{
    QStringList listPatient = db.getPatientList();
    lwPatient->clear();
    lwPatient->addItems(listPatient);
    stackWidget->setCurrentWidget(lwPatient);
}

void Admin::on_btnExit_clicked()
{
    this->close();
    if(mainWindow) mainWindow->show();
}

Admin::~Admin() {}
