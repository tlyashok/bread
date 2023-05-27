#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class taskForm;
}

class taskForm : public QWidget, public Singleton<taskForm>
{
    Q_OBJECT

private:
    explicit taskForm(QWidget *parent = nullptr);
    ~taskForm();
    friend class Singleton<taskForm>;

public slots:
    ///
    /// \brief selectTask
    /// \param task Номер задания.
    /// \param seed Вариант задания.
    /// \param task_text Текст задания.
    ///
    /// Принимает информацию о задании.
    ///
    void selectTask(int task, int seed, QString task_text);

signals:
    ///
    /// \brief sendAnswer
    /// \param task
    /// \param seed
    /// \param answer
    ///
    /// Отправляет ответ на задание.
    ///
    void sendAnswer(int task, int seed, QString answer);

private slots:
    void on_pushButton_send_clicked();

private:
    Ui::taskForm *ui;
    ///
    /// \brief task
    ///
    /// Номер задания.
    ///
    /// \brief seed
    ///
    /// Сид задания.
    ///
    int task, seed;
};

#endif // TASKFORM_H
