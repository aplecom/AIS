#include "admin.h"

Admin::Admin(DataBase &database, QWidget* mainWindow, QWidget* parent)
    : QWidget(parent), db(database), mainWindow(mainWindow)
{
    admDesign();
    connect(btnDoctors,&QPushButton::clicked,this,&Admin::on_btnDoctors_clicked);
    connect(btnPatients, &QPushButton::clicked, this, &Admin::on_btnPatients_clicked);
    connect(btnExit,&QPushButton::clicked, this, &Admin::on_btnExit_clicked);
    connect(btnBack1,&QPushButton::clicked,this,&Admin::showMainMenu);
    connect(btnBack2,&QPushButton::clicked,this,&Admin::showMainMenu);
    connect(btnRemovePatient,&QPushButton::clicked,this,&Admin::on_btnRemovePatient);
}

void Admin::admDesign()
{
    setMinimumSize(WIDTH,HEIGHT);
    setWindowTitle("Администратор");

    QPixmap background(":/img/img/background.jpg");
    QPixmap logo(":/img/img/logo.png");
    logo = logo.scaled(150, 150, Qt::KeepAspectRatio);

    QPalette  palette;
    palette.setBrush(QPalette::Background, QBrush(background));
    setPalette(palette);


    menuStack = new QStackedWidget(this);
    mainMenu = new QWidget();
    mainMenuLayout = new QVBoxLayout(mainMenu);

    btnDoctors = new QPushButton("Доктора",this);
    btnPatients =  new QPushButton("Пациенты",this);
    btnExit =new QPushButton("Выйти",this);


    lbLogo = new QLabel(this);
    lbLogo->setPixmap(logo);
    lbLogo->setFixedSize(200,200);


    mainMenuLayout->addWidget(lbLogo);
    mainMenuLayout->addWidget(btnDoctors);
    mainMenuLayout->addWidget(btnPatients);
    mainMenuLayout->addWidget(btnExit);

    doctorMenu = new QWidget();
    doctorsMenuLayout = new QVBoxLayout(doctorMenu);
    btnBack1 = new QPushButton("Назад", this);
    doctorsMenuLayout->addWidget(btnBack1);

    patientMenu = new QWidget();
    patienstMenuMenuLayout = new QVBoxLayout(patientMenu);
    btnBack2 = new QPushButton("Назад", this);
    btnAddPatient = new QPushButton("Добавить", this);
    btnRemovePatient = new QPushButton("Удалить", this);
    patienstMenuMenuLayout->addWidget(btnAddPatient);
    patienstMenuMenuLayout->addWidget(btnRemovePatient);
    patienstMenuMenuLayout->addWidget(btnBack2);

    menuStack->addWidget(mainMenu);
    menuStack->addWidget(doctorMenu);
    menuStack->addWidget(patientMenu);
    menuStack->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    stackWidget = new QStackedWidget(this);

    lWDoctors = new QListWidget();
    lwPatient = new QListWidget();
    stackWidget->addWidget(lWDoctors);
    stackWidget->addWidget(lwPatient);

    gLayout = new QGridLayout(this);
    gLayout->addWidget(stackWidget,0,1,4,3);
    gLayout->addWidget(menuStack,0,0,4,1);

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
    lWDoctors->addItems(listDoctors);
    stackWidget->setCurrentWidget(lWDoctors);
    menuStack->setCurrentWidget(doctorMenu);
}

void Admin::on_btnPatients_clicked()
{
    QStringList listPatient = db.getPatientList();
    lwPatient->addItems(listPatient);
    stackWidget->setCurrentWidget(lwPatient);
    menuStack->setCurrentWidget(patientMenu);

}

void Admin::on_btnExit_clicked()
{
    this->close();
    if(mainWindow) mainWindow->show();
}

void Admin:: showMainMenu()
{
    menuStack->setCurrentWidget(mainMenu);
    lWDoctors->clear();
    lwPatient->clear();
}

void Admin::on_btnAddPatient()
{

}

void Admin::on_btnRemovePatient()
{
   QListWidgetItem* selectedItem = lwPatient->currentItem();

   if(selectedItem)
   {
       QString selectedPatient = selectedItem->text();
       QStringList parts = selectedPatient.split(" : ");
       QString patientID = parts[0];
       db.removePatient(patientID);

       lwPatient->clear();
       QStringList updateList = db.getPatientList();
       lwPatient->addItems(updateList);
   }
}
Admin::~Admin() {}
