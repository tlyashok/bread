#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QStackedWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include "mainform.h"
#include "authform.h"
#include "taskform.h"
#include "teacherform.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget* parent);
    ~Client();

private:
    QString user_login;
    QString user_pass;
    bool auth_stat = false;
    bool is_teacher = false;
    ///
    /// \brief qsw
    ///
    /// Хранит в себе все формы: авторизации, главную и задания.
    ///
    QStackedWidget* qsw;
    ///
    /// \brief af
    ///
    /// Форма авторизации.
    ///
    authForm* af;
    ///
    /// \brief mf
    ///
    /// Главная форма, где происходит просмотр и выбор заданий.
    ///
    mainForm* mf;
    ///
    /// \brief tf
    ///
    /// Форма выполнения задания.
    ///
    taskForm* tf;
    ///
    /// \brief tef
    ///
    /// Форма для просмотра преподавателем статистики по студентам
    ///
    teacherForm* tef;
    ///
    /// \brief authVer
    /// \param result Результат запроса, 0 или 1
    /// \param isATeacher Является ли пользователь преподавателем
    ///
    /// Проверка результата запроса на авторизацию
    ///
    void authVer(int result, int isATeacher);
    ///
    /// \brief regVer
    /// \param result
    ///
    /// Проверка результата запроса на регистрацию
    ///
    void regVer(int result);
    ///
    /// \brief selectTaskVer
    /// \param task Текст задачи
    /// \param seed Вариант задачи
    ///
    /// Получение текста задачи и сида (варианта задания)
    ///
    void selectTaskVer(int task, int seed, QString task_text);
    ///
    /// \brief getStudentNamesVer
    /// \param student_names имена студентов, разделенные пробелами
    ///
    /// Получение списка имен студентов
    ///
    void getStudentNamesVer(QStringList student_names);
    ///
    /// \brief getStudentStatisticsVer
    /// \param name имя студента
    /// \param task_id номер задания
    /// \param successes
    /// \param failures
    /// \param last_failure
    ///
    void getStudentStatisticsVer(QString name, int task_id, int successes, int failures, int last_failure);
    ///
    /// \brief closeEvent
    /// \param event
    ///
    /// Переопределение события закрытия окна
    ///
    void closeEvent(QCloseEvent* event);

signals:
    ///
    /// \brief selectTaskGenerated
    /// \param task Номер задания
    /// \param seed Вариант задания
    /// \param task_text Текст задания
    ///
    /// Отправляется в taskForm, передает полученные номер задания и сид.
    ///
    void selectTaskGenerated(int task, int seed, QString task_text);
    ///
    /// \brief sendStudentStatistics
    /// \param name имя студента
    /// \param task_id номер задания
    /// \param successes число правильно выполненных заданий
    /// \param failures число неверно выполненных заданий
    /// \param last_failure номер последней ошибки
    ///
    /// Отправляется в teacherForm, передает информацию по студентам
    ///
    void sendStudentStatistics(QString name, int task_id, int successes, int failures, int last_failure);

private slots:
    ///
    /// \brief auth
    /// \param login
    /// \param password
    ///
    /// Принимает сигнал из authForm, отправляет запрос аутентификации на сервер.
    ///
    void auth(QString login, QString password);
    ///
    /// \brief reg
    /// \param login
    /// \param password
    /// \param studentOrTeacher
    /// \param teacherCode
    ///
    /// Принимает сигнал из authForm, отправляет запрос регистрации на сервер.
    ///
    void reg(QString login, QString password, bool studentOrTeacher, QString teacherCode);
    ///
    /// \brief exit
    ///
    /// Принимает сигнал из mainForm, выходит на страницу авторизации.
    ///
    void exit();
    ///
    /// \brief selectTask
    /// \param task
    ///
    /// Принимает сигнал из mainForm, отправляет запрос на получение сида для задания.
    ///
    void selectTask(int task);
    ///
    /// \brief sendAnswer
    /// \param task
    /// \param seed
    /// \param answer
    ///
    /// Принимает сигнал из taskForm, отправляет ответ на задание на сервер, получает сид
    /// и отправляет selectTaskGenerated.
    ///
    void sendAnswer(int task, int seed, QString answer);
    void parser(QString serv_answer);
};
#endif // MAINWINDOW_H
