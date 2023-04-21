#include "mainform.h"
#include "ui_mainform.h"

mainForm::mainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainForm)
{
    ui->setupUi(this);
}

mainForm::~mainForm()
{
    delete ui;
}

void mainForm::on_pushButton_exit_clicked()
{
    emit this->exit();
}


void mainForm::on_pushButton_task1_clicked()
{
    emit this->selectTask(1);
}


void mainForm::on_pushButton_task2_clicked()
{
    emit this->selectTask(2);
}


void mainForm::on_pushButton_task3_clicked()
{
    emit this->selectTask(3);
}


void mainForm::on_pushButton_task4_clicked()
{
    emit this->selectTask(4);
}


void mainForm::on_pushButton_task5_clicked()
{
    emit this->selectTask(5);
}

