#include "admin.h"

Admin::Admin(DataBase &database, QWidget* mainWindow, QWidget* parent)
    : QWidget(parent), db(database), mainWindow(mainWindow)
{
    admDesign();
    connect(btnDoctors,&QPushButton::clicked,this,&Admin::on_btnDoctors_clicked);
    connect(btnPatients, &QPushButton::clicked, this, &Admin::on_btnPatients_clicked);
    connect(btnExit,&QPushButton::clicked, this, &Admin::on_btnExit_clicked);
    connect(btnBackDocInMenu,&QPushButton::clicked,this,&Admin::showMainMenu);
    connect(btnBackPacInMenu,&QPushButton::clicked,this,&Admin::showMainMenu);
    connect(btnRemovePatient,&QPushButton::clicked,this,&Admin::on_btnRemovePatient);
    connect(btnAddPatient1,&QPushButton::clicked,this,&Admin::on_btnAddPatient1);
    connect(btnAddPatient2,&QPushButton::clicked,this,&Admin::on_btnAddPatient2);
    connect(btnBackPatInList, &QPushButton::clicked,this, &Admin::on_btnBackPatInList);
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
    btnBackDocInMenu = new QPushButton("Назад", this);
    doctorsMenuLayout->addWidget(btnBackDocInMenu);

    patientMenu = new QWidget();
    patienstMenuLayout = new QVBoxLayout(patientMenu);
    btnBackPacInMenu = new QPushButton("Назад", this);
    btnAddPatient1 = new QPushButton("Добавить", this);
    btnRemovePatient = new QPushButton("Удалить", this);
    patienstMenuLayout->addWidget(btnAddPatient1);
    patienstMenuLayout->addWidget(btnRemovePatient);
    patienstMenuLayout->addWidget(btnBackPacInMenu);

    menuStack->addWidget(mainMenu);
    menuStack->addWidget(doctorMenu);
    menuStack->addWidget(patientMenu);

    menuStack->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    infoStack = new QStackedWidget(this);

    lWDoctors = new QListWidget();
    lwPatient = new QListWidget();
    infoAddPatient = new QWidget();
    infoStack->addWidget(lWDoctors);
    infoStack->addWidget(lwPatient);
    infoStack->addWidget(infoAddPatient);

    gLayout = new QGridLayout(this);
    gLayout->addWidget(infoStack,0,1,4,3);
    gLayout->addWidget(menuStack,0,0,4,1);

    lbLogo->setStyleSheet("margin-left: 30px; ");
    infoStack->setStyleSheet("font-size: 20px; ");

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

    patientAddMenu = new QWidget();
    patientsAddLayout = new QVBoxLayout(patientAddMenu);
    btnAddPatient2 = new QPushButton("+",this);
    btnBackPatInList = new QPushButton("Назад к списку",this);
    patientsAddLayout->addWidget(btnAddPatient2);
    patientsAddLayout->addWidget(btnBackPatInList);

    menuStack->addWidget(patientAddMenu);

    design_infoAddPatient();

}

void Admin::on_btnDoctors_clicked()
{
    QStringList listDoctors = db.getDoctorsList();
    lWDoctors->addItems(listDoctors);
    infoStack->setCurrentWidget(lWDoctors);
    menuStack->setCurrentWidget(doctorMenu);
}

void Admin::on_btnPatients_clicked()
{
    QStringList listPatient = db.getPatientList();
    lwPatient->addItems(listPatient);
    infoStack->setCurrentWidget(lwPatient);
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

void Admin::on_btnAddPatient1()
{
    menuStack->setCurrentWidget(patientAddMenu);
    infoStack->setCurrentWidget(infoAddPatient);
}

void Admin::on_btnAddPatient2()
{
    // db.addPatient
}

void Admin::on_btnBackPatInList()
{
    menuStack->setCurrentWidget(patientMenu);
    infoStack->setCurrentWidget(lwPatient);
}

void Admin::design_infoAddPatient()
{

    nameLt = new QHBoxLayout();
    lastNameLt = new QHBoxLayout();
    dateLt = new QHBoxLayout();
    phoneLt = new QHBoxLayout();
    addPatLt = new QVBoxLayout(infoAddPatient);

    lEditName = new QLineEdit(this);
    lEditLastName = new QLineEdit(this);
    lEditDate = new QLineEdit(this);
    lEditPhone = new QLineEdit(this);

    lEditName->setPlaceholderText("Иван");
    lEditLastName->setPlaceholderText("Иванов");
    lEditDate->setPlaceholderText("год-месяц-день");
    lEditPhone->setPlaceholderText("+7 901 194 32 66");

    lbLogo = new QLabel(this);
    lbName = new QLabel("Имя: ",this);
    lbLastName = new QLabel("Фамилия: ",this);
    lbDate = new QLabel("Дата: ",this);
    lbPhone = new QLabel("Телефон: ",this);


    nameLt->addWidget(lbName);
    nameLt->addWidget(lEditName);

    lastNameLt->addWidget(lbLastName);
    lastNameLt->addWidget(lEditLastName);

    dateLt->addWidget(lbDate);
    dateLt->addWidget(lEditDate);

    phoneLt->addWidget(lbPhone);
    phoneLt->addWidget(lEditPhone);


    addPatLt->addLayout(nameLt);
    addPatLt->addLayout(lastNameLt);
    addPatLt->addLayout(dateLt);
    addPatLt->addLayout(phoneLt);
}

Admin::~Admin() {}
