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
    connect(btnAddMeet, &QPushButton::clicked,this,&Admin::on_btnAddMeet);
    connect(btnBackDocInList, &QPushButton::clicked,this, &Admin::on_btnBackDocInList);
    connect(btnLookMeetings,&QPushButton::clicked,this,&Admin::on_btnLookMeetings);
    connect(btnBackDocInListForLook, &QPushButton::clicked,this, &Admin::on_btnBackDocInList);
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
    btnAddMeet = new QPushButton("Добавить прием",this);
    btnLookMeetings = new QPushButton("Посмотреть приемы",this);
    btnBackDocInMenu = new QPushButton("Назад", this);
    doctorsMenuLayout->addWidget(btnAddMeet);
    doctorsMenuLayout->addWidget(btnLookMeetings);
    doctorsMenuLayout->addWidget(btnBackDocInMenu);


    patientMenu = new QWidget();
    patienstMenuLayout = new QVBoxLayout(patientMenu);
    btnBackPacInMenu = new QPushButton("Назад", this);
    btnAddPatient1 = new QPushButton("Добавить", this);
    btnRemovePatient = new QPushButton("Удалить", this);
    patienstMenuLayout->addWidget(btnAddPatient1);
    patienstMenuLayout->addWidget(btnRemovePatient);
    patienstMenuLayout->addWidget(btnBackPacInMenu);

    addMeetMenu = new QWidget();
    meetMenuLayotC = new QVBoxLayout(addMeetMenu) ;
    btnBackDocInList = new QPushButton("Назад",this);
    meetMenuLayotC->addWidget(btnBackDocInList);

    lookMeetingsMenu = new QWidget();
    lookMeetingsMenuLayout =  new QVBoxLayout(lookMeetingsMenu);
    btnBackDocInListForLook = new QPushButton("Назад", this);
    lookMeetingsMenuLayout->addWidget(btnBackDocInListForLook);


    menuStack->addWidget(mainMenu);
    menuStack->addWidget(doctorMenu);
    menuStack->addWidget(patientMenu);
    menuStack->addWidget(addMeetMenu);
    menuStack->addWidget(lookMeetingsMenu);

    menuStack->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    infoStack = new QStackedWidget(this);

    lWDoctors = new QListWidget();
    lwPatient = new QListWidget();
    infoAddPatient = new QWidget();
    calendar = new QCalendarWidget();
    infoStack->addWidget(lWDoctors);
    infoStack->addWidget(lwPatient);
    infoStack->addWidget(infoAddPatient);
    infoStack->addWidget(calendar);

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
    btnAddPatient2 = new QPushButton("Добавить пациента",this);
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
    lEditName->clear();
    lEditLastName->clear();
    lEditPhone->clear();
    infoStack->setCurrentWidget(infoAddPatient);
}

void Admin::on_btnAddPatient2()
{
    QString name = lEditName->text();
    QString lastN = lEditLastName->text();
    QDate date = lEditDate->date();
    QString phone = lEditPhone->text();

    bool ok_phone;
    bool not_name;
    bool not_lastName;
    phone.toInt(&ok_phone);
    name.toInt(&not_name);
    lastN.toInt(&not_lastName);

    if(name.isEmpty() || not_name)
    {
        lEditName->clear();
        clearInfoLb();
        qDebug()<<"Некорректное имя!";
        infoName->setText("Некорректное имя!");
        return;
    }

    else if(lastN.isEmpty() || not_lastName)
    {
        lEditLastName->clear();
        clearInfoLb();
        qDebug()<<"Некорректная фамилия!";
        infoLastName->setText("Некорректная фамилия!");
        return;
    }

    else if(!date.isValid())
    {
       clearInfoLb();
       qDebug()<<"Некорректная дата!";
       infoDate->setText("Некорректная дата!");
       return;
    }
    else if(!ok_phone && phone.length()!=11)
    {
        lEditPhone->clear();
        clearInfoLb();
        qDebug()<<"Некорректный телефон!";
        infoPhone->setText("Некорректный телефон!");
        return;
    }
    else
    {
        db.addPatient(name,lastN,date,phone);
        clearInfoLb();
        clearDatePatLb();
        sucAddPat->setText("Пациент успешно добавлен!");
    }
}

void Admin::on_btnBackPatInList()
{
    menuStack->setCurrentWidget(patientMenu);

    lwPatient->clear();
    lwPatient->addItems(db.getPatientList());
    clearInfoLb();
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
    lEditDate = new QDateEdit(this);
    lEditPhone = new QLineEdit(this);

    lEditName->setPlaceholderText("Иван");
    lEditLastName->setPlaceholderText("Иванов");
    lEditPhone->setPlaceholderText("89011943266");

    lbLogo = new QLabel(this);
    lbName = new QLabel("Имя: ",this);
    lbLastName = new QLabel("Фамилия: ",this);
    lbDate = new QLabel("Дата: ",this);
    lbPhone = new QLabel("Телефон: ",this);


    infoName = new QLabel(this);
    infoLastName = new QLabel(this);
    infoDate = new QLabel(this);
    infoPhone = new QLabel(this);

    sucAddPat = new QLabel(this);

    nameLt->addWidget(lbName);
    nameLt->addWidget(lEditName);

    lastNameLt->addWidget(lbLastName);
    lastNameLt->addWidget(lEditLastName);

    dateLt->addWidget(lbDate);
    dateLt->addWidget(lEditDate);

    phoneLt->addWidget(lbPhone);
    phoneLt->addWidget(lEditPhone);

    addPatLt->addLayout(nameLt);
    addPatLt->addWidget(infoName);
    infoName->setStyleSheet("color: red");

    addPatLt->addLayout(lastNameLt);
    addPatLt->addWidget(infoLastName);
    infoLastName->setStyleSheet("color: red");

    addPatLt->addLayout(dateLt);
    addPatLt->addWidget(infoDate);
    infoDate->setStyleSheet("color: red");

    addPatLt->addLayout(phoneLt);
    addPatLt->addWidget(infoPhone);
    infoPhone->setStyleSheet("color: red");

    addPatLt->addWidget(sucAddPat);
    sucAddPat->setStyleSheet("color: black");

}

void Admin::clearInfoLb()
{
    infoName->clear();
    infoLastName->clear();
    infoDate->clear();
    infoPhone->clear();
    sucAddPat->clear();
}

void Admin::clearDatePatLb()
{
    lEditName->clear();
    lEditLastName->clear();
    lEditPhone->clear();
}

void Admin::on_btnAddMeet()
{
    menuStack->setCurrentWidget(addMeetMenu);
    infoStack->setCurrentWidget(calendar);
}

void Admin::on_btnBackDocInList()
{
    menuStack->setCurrentWidget(doctorMenu);
    infoStack->setCurrentWidget(lWDoctors);
}

void Admin::on_btnLookMeetings()
{
    menuStack->setCurrentWidget(lookMeetingsMenu);
    // тут виджет справа подумать для вывода приемов
}


Admin::~Admin() {}
