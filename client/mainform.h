#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class mainForm;
}

class mainForm : public QWidget
{
    Q_OBJECT

signals:
    void exit();
    void selectTask(int task);

public:
    explicit mainForm(QWidget *parent = nullptr);
    ~mainForm();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_task1_clicked();

    void on_pushButton_task2_clicked();

    void on_pushButton_task3_clicked();

    void on_pushButton_task4_clicked();

    void on_pushButton_task5_clicked();

private:
    Ui::mainForm *ui;
};

#endif // MAINFORM_H
