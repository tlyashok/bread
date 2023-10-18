#include "teacherform.h"
#include "ui_teacherform.h"

teacherForm::teacherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherForm)
{
    ui->setupUi(this);
}

teacherForm::~teacherForm()
{
    delete ui;
}

void teacherForm::on_exitButton_clicked()
{
    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
    emit this->exit();
}

void teacherForm::getStudentData(QString name, int task_id, int successes, int failures, int last_failure) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(task_id)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(successes)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(failures)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(last_failure)));
}
