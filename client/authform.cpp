#include "authform.h"
#include "ui_authform.h"

authForm::authForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authForm)
{
    ui->setupUi(this);
    this->authOrReg = false;
    this->setAuthOrReg();
}

authForm::~authForm()
{
    delete ui;
}

void authForm::setAuthOrReg()
{
    this->ui->label_email->setVisible(this->authOrReg);
    this->ui->lineEdit_email->setVisible(this->authOrReg);
    if (this->authOrReg)
    {
        this->ui->pushButton_auth_or_reg->setText("Зарегистрироваться");
        this->ui->pushButton_switch->setText("Перейти к авторизации");
    }
    else
    {
        this->ui->pushButton_auth_or_reg->setText("Авторизоваться");
        this->ui->pushButton_switch->setText("Перейти к регистрации");

    }
}
void authForm::on_pushButton_switch_clicked()
{
    this->authOrReg = !this->authOrReg;
    this->setAuthOrReg();
}


void authForm::on_pushButton_auth_or_reg_clicked()
{
    if(this->authOrReg)
        emit this->reg(this->ui->lineEdit_login->text(),
                       this->ui->lineEdit_password->text(),
                       this->ui->lineEdit_email->text());
    emit this->auth(this->ui->lineEdit_login->text(),
                   this->ui->lineEdit_password->text());
}

