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
    void selectTask(int task);

signals:
    void sendAnswer(int task, int seed, QString answer);

private slots:
    void on_pushButton_send_clicked();

private:
    Ui::taskForm *ui;
    int task, seed;
};

#endif // TASKFORM_H
