#include "taskform.h"
#include "ui_taskform.h"

taskForm::taskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskForm)
{
    ui->setupUi(this);
}

taskForm::~taskForm()
{
    delete ui;
}

void taskForm::selectTask(int task)
{
    this->task = task;
    this->seed = 666; // надо отсылать запрос к DB для получения сида
    this->ui->label_task_number->setText("Номер задания: "+QString::number(this->task));
}

void taskForm::on_pushButton_send_clicked()
{
    emit this->sendAnswer(this->task, this->seed, this->ui->lineEdit_answer->text());
}

