#include "taskform.h"
#include "ui_taskform.h"
#include "singleclient.h"

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

void taskForm::selectTask(int task, int seed, QString task_text)
{
    SingletonClient::getInstance()->sendToServer(QString::number(task).toUtf8());
    this->task = task;
    this->seed = seed; // надо отсылать запрос к DB для получения сида
    this->ui->label_task_number->setText("Номер задания: "+QString::number(this->task));
    this->ui->label_task_seed->setText("Вариант задания: "+QString::number(this->seed));
    this->ui->label->setText(task_text);
}

void taskForm::on_pushButton_send_clicked()
{
    emit this->sendAnswer(this->task, this->seed, this->ui->lineEdit_answer->text());
}

