#ifndef TEACHERFORM_H
#define TEACHERFORM_H

#include <QWidget>
#include "QDebug"
#include "singleton.h"

namespace Ui {
class teacherForm;
}

class teacherForm : public QWidget, public Singleton<teacherForm>
{
    Q_OBJECT

public:
    explicit teacherForm(QWidget *parent = nullptr);
    ~teacherForm();
    friend class Singleton<teacherForm>;
signals:
    ///
    /// \brief exit
    ///
    /// Вызывает закрытие программы.
    ///
    void exit();
public slots:
    void getStudentData(QString name, int task_id, int successes, int failures, int last_failure);
private slots:
    void on_exitButton_clicked();

private:
    Ui::teacherForm *ui;
};

#endif // TEACHERFORM_H
