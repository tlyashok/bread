#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>

namespace Ui {
class taskForm;
}

class taskForm : public QWidget
{
    Q_OBJECT

public:
    explicit taskForm(QWidget *parent = nullptr);
    ~taskForm();

public slots:
    ///
    /// \brief selectTask
    /// \param task
    ///
    /// Принимает информацию о задании.
    ///
    void selectTask(int task, int seed);

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
