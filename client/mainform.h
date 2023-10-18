#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class mainForm;
}

class mainForm : public QWidget, public Singleton<mainForm>
{
    Q_OBJECT

signals:
    ///
    /// \brief exit
    ///
    /// Вызывает закрытие программы.
    ///
    void exit();
    ///
    /// \brief selectTask
    /// \param task
    ///
    /// Вызывавет выбор задания и переход к taskForm.
    ///
    void selectTask(int task);

private:
    friend class Singleton<mainForm>;
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
