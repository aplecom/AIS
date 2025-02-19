#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent)
{
    db.createConnection();
    mWindDesign();
    connect(btnLogIn,&QPushButton::clicked,this,&MainWindow::on_btnLogIn_button_clicked);
}

void MainWindow::mWindDesign()
{
    QPixmap background(":/img/img/background.jpg");
    QPixmap logo(":/img/img/logo.png");
    logo = logo.scaled(80, 80, Qt::KeepAspectRatio);

    QPalette  palette;
    palette.setBrush(QPalette::Background, QBrush(background));
    setPalette(palette);

    setWindowTitle("Регистратурка");
    setMinimumSize(WIDTH,HEIGHT);

    layout = new QVBoxLayout(this);
    layoutHeader = new QHBoxLayout();
    lbHeader = new QLabel("Регистратура",this);
    lnEdLogin = new QLineEdit(this);
    lnEdPassword = new QLineEdit(this);
    btnLogIn = new QPushButton("Войти",this);

    lbLogo = new QLabel(this);
    lbLogo->setPixmap(logo);
    lbLogo->setFixedSize(80,80);


    layoutHeader->addWidget(lbLogo);
    layoutHeader->addWidget(lbHeader);
    layout->addLayout(layoutHeader);
    layout->addWidget(lnEdLogin);
    layout->addWidget(lnEdPassword);
    layout->addWidget(btnLogIn);

    lnEdLogin->setPlaceholderText("Логин");
    lnEdPassword->setPlaceholderText("Пароль");

    layoutHeader->setAlignment(Qt::AlignCenter);
    lbLogo->setAlignment(Qt::AlignCenter);
    lbHeader->setAlignment(Qt::AlignCenter);

    lnEdLogin->setAlignment(Qt::AlignCenter);
    lnEdPassword->setAlignment(Qt::AlignCenter);
    lnEdPassword->setEchoMode(QLineEdit::Password);

    lbLogo->setStyleSheet("margin: 0px 0px 0px 0px;");
    lbHeader->setStyleSheet("font-size: 40px;");
    lnEdLogin->setStyleSheet("font-size: 20px; border-radius: 10px; border: 2px solid black ; padding: 5px; margin: 0px 100px 10px 100px;");
    lnEdPassword->setStyleSheet("font-size: 20px; border-radius: 10px; border: 2px solid black; padding: 5px; margin: 10px 100px 10px 100px;");
    btnLogIn->setStyleSheet("font-size: 20px; padding: 5px; margin: 10px 300px 200px 300px;");

    // блок заглушка для быстрой проверки второго виджета
    lnEdLogin->setText("admin");
    lnEdPassword->setText("admin");
    // блок заглушка для быстрой проверки второго виджета

}

void MainWindow::on_btnLogIn_button_clicked()
{
    newLogin = lnEdLogin->text();
    newPassword = lnEdPassword->text();
    if(db.autoUser(newLogin,newPassword) == "Админ")
    {
        this->close();
        admin = new Admin(db,nullptr);
        admin->show();
    }
}

MainWindow:: ~MainWindow(){
    delete admin;
}
