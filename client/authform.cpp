#include "authform.h"
#include "ui_authform.h"
#include "singleclient.h"

authForm::authForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authForm)
{
    ui->setupUi(this);
    this->authOrReg = false;
    this->studentOrTeacher = false;
    this->uiReset();
}
authForm::~authForm()
{
    delete ui;
}

void authForm::uiReset()
{
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
    if (this->studentOrTeacher)
        this->ui->pushButton_regtype->setText("Преподаватель");
    else
        this->ui->pushButton_regtype->setText("Студент");
    this->ui->pushButton_regtype->setVisible(this->authOrReg);
    this->ui->label_teacher_code->setVisible(this->authOrReg && !this->studentOrTeacher);
    this->ui->lineEdit_teacher_code->setVisible(this->authOrReg && !this->studentOrTeacher);
}
void authForm::on_pushButton_switch_clicked()
{
    this->authOrReg = !this->authOrReg;
    this->uiReset();
}


void authForm::on_pushButton_auth_or_reg_clicked()
{
    if(this->authOrReg)
        emit this->reg(this->ui->lineEdit_login->text(),
                       this->ui->lineEdit_password->text(),
                       this->studentOrTeacher,
                       this->ui->lineEdit_teacher_code->text());
    else {
        emit this->auth(this->ui->lineEdit_login->text(),
                    this->ui->lineEdit_password->text());
    }
}

void authForm::auth_user()
{
    emit this->auth(this->ui->lineEdit_login->text(),
                this->ui->lineEdit_password->text());
}

void authForm::on_pushButton_regtype_clicked()
{
    this->studentOrTeacher = !this->studentOrTeacher;
    this->uiReset();
}
